# 消息传递框架与完整的ATM示例

```c++
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

namespace messaging
{
    struct message_base // 队列项的基础类
    {
        virtual ~message_base() {}
    };

    template<typename Msg>
    struct wrapped_message : message_base // 每个消息类型都需要特化
    {
        Msg contents;
        explicit wraped_message(Msg const& contents_) : contents(contents_){}
    };

    class queue // 我们的队列
    {
        std::mutex m;
        std::condition_variable c;
        std::queue<std::shared_ptr<message_base> > q; // 实际存储指向message_base
    public:
        template<typename T>
        void push(T const& msg)
        {
            std::lock_guard<std::mutex> lk(m);
            q.push(std::make_shared<wrapped_message<T> >(msg)); // 包装已传递的信息
            c.notify_all();
        }

        std::shared_ptr<message_base> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(m);
            c.wait(lk, [&]{return !q.empty();}); // 当队列为空时阻塞
            auto res = q.front();
            q.pop();
            return res;
        }
    };

    class sender
    {
        queue* q; // sender是一个队列指针的包装类
    public:
        sender():q(nullptr){} // sender无队列(默认构造函数)
        explicit sender(queue* q_) : q(q_) {} // 从指向队列的指针进行构造

        template<typename Message>
        void send(Message const& msg)
        {
            if(q)
            {
                q-push(msg); // 将发送信息推送给队列
            }
        }
    };

    class receiver
    {
        queue q; // 接受者拥有对应队列
    public:
        operator sender() // 允许将类中队列隐式转化为一个sender队列
        {
            return sender(&q);
        }
        dispatcher wait() // 等待对队列进行调度
        {
            return dispatcher(&q);
        }
    };

    class close_queue{}; // 用于关闭队列的消息

    class dispatcher
    {
        queue* q;
        bool chained;

        dispatcher(dispatcher const&)=delete; // dispatcher实例不能被拷贝
        dispatcher& operator=(dispatcher const&)=delete;

        template<
            typename Dispatcher,
            typename Msg,
            typename Func> // 允许TemplateDispatcher实例访问内部成员
        friend class TemplateDispatcher;

        void wait_and_dispatch()
        {
            for(;;) // 1 循环，等待调度消息
            {
                auto msg = q->wait_and_pop();
                dispatch(msg);
            }
        }

        bool dispatch( // 2 dispatch()会检查close_queue消息，然后抛出
                std::shared_ptr<message_base> const& msg)
        {
            if(dynamic_cast<wrapped_message<close_queue>*>(msg.get()))
            {
                throw close_queue();
            }
            return false;
        }
    public:
        dispatcher(dispatcher&& other) : q(other.q), chained(other.chained) // 调度器实例可以被移动
        {
            other.chained = true; // 来源不得等待消息
        }
        explicit dispatcher(queue* q_) : q(q_), chained(false){}
        
        template<typename Message, typename Func>
        TemplateDispatcher<dispatcher, Message, Func>
        handle(Func&& f) // 使用TemplateDispatcher处理特定类型的消息
        {
            return TemplateDispatcher<dispatcher, Message, Func>(q, this, std::forward<Func>(f));
        }
        ~dispatcher() noexcept(false) // 析构函数可能抛出异常
        {
            if(!chained)
            {
                wait_and_dispatch();
            }
        }
    };
    
    template<typename PreviousDispatcher, typename Msg, typename Func>
    class TemplateDispatcher
    {
        queue* q;
        PreviousDispatcher* prev;
        Func f;
        bool chained;

        TemplateDispatcher(TemplateDispatcher const&) = delete;
        TempalteDispatcher& operator=(TempalteDispatcher const&) = delete;

        template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
        friend class TemplateDispatcher;        // TemplateDispatcher实例之间互为友元

        void wait_and_dispatch()
        {
            for(;;)
            {
                auto msg = q->wait_and_pop();
                if(dispatch(msg))               // 如果我们处理了消息，跳出循环
                    break;
            }
        }
        bool dispatch(std::shared_ptr<message_base> const& msg)
        {
            if(wrapped_message<Msg>* wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) // 检查消息类型并调用函数
            {
                f(wrapper->contents);
                return true;
            }
            else
            {
                return prev->dispatch(msg);     // 链至前一个调度器
            }
        }
    public:
        TemplateDispatcher(TemplateDispatcher&& other) : 
            q(other.q), prev(other.prev), f(std::move(other.f)),
            chained(other.chained)
        {
            other.chained = true;
        }
        TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_) :
            q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false)
        {
            prev_->chained = true;
        }
        template<typename OtherMsg, typename OtherFunc>
        TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
        handle(OtherFunc&& of)                  // 可以链接附加的处理函数
        {
            return TemplateDispatcher<
                TemplateDispatcher, OtherMsg, OtherFunc>(
                        q, this, std::forward<OtherFunc>(of));
        }
        ~TemplateDispatcher() noexcept(false)   // 析构函数又是noexcept(false)的
        {
            if(!chained)
            {
                wait_and_dispatch();
            }
        }
    };

    struct withdraw
    {
        std::string account;
        unsigned amount;
        mutable messaging::sender atm_queue;

        withdraw(std::string const& account_,
                 unsigned amount_,
                 messaging::sender atm_queue_) :
            account(account_), amount(amout_), atm_quue(atm_queue_) {}
    };

    struct withdraw_ok {};
    struct withdraw_denied {};
    struct cancel_withdrawal
    {
        std::string account;
        unsigned amount;
        cancel_withdrawal(std::string const& account_, unsigned amount_) :
            account(account_), amount(amount_) {}
    };

    struct withdrawal_processed
    {
        std::string account;
        unsigned amount;
        withdrawal_processed(std::string const& account_, unsigned amount_) :
            account(account_), amount(amount_) {};
    };

    struct card_inserted
    {
        std::string account;
        explicit card_inserted(std::string const& account_) : account(account_) {}
    };

    struct digit_pressed
    {
        char digit;
        explicit digit_pressed(char digit_) : digit(digit_) {}
    };

    struct clear_last_pressed{};
    
    struct eject_card{};

    struct withdraw_pressed
    {
        unsigned amount;
        explicit withdraw_pressed(unsigned amount_) : amount(amount_) {}
    };
    struct cancel_pressed{};
    struct issue_money
    {
    
    }
}


```

