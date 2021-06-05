# strand
### 摘要

定义了事件处理程序的严格顺序调用,实现类似于管道的功能；

### 用法

```c++
#include <iostream>
#include <thread>
//简单日志宏，打印日志及附加的线程ID
#define  LOG(a) std::cout<<"[T"<<std::this_thread::get_id()<<"]"<<a<<"\n"
 
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include<boost/bind.hpp>
#include<boost/asio/strand.hpp>
 
 
class Printer
{
public:
	Printer(boost::asio::io_context& ioc)
		:m_strand(ioc), 
		m_timer1(ioc, boost::posix_time::seconds(1)),
		m_timer2(ioc, boost::posix_time::seconds(1))
	{
		m_timer1.async_wait(boost::asio::bind_executor(m_strand, boost::bind(&Printer::print1, this)));
		m_timer2.async_wait(boost::asio::bind_executor(m_strand, boost::bind(&Printer::print2, this)));
		//m_timer1.async_wait(boost::bind(&Printer::print1, this));
		//m_timer2.async_wait(boost::bind(&Printer::print2, this));
	}
 
	void print1()
	{
		if (m_count++< 10)
		{
			LOG("print 1 ...count "<<m_count);
			m_timer1.expires_at(m_timer1.expires_at() + boost::posix_time::seconds(1));
			m_timer1.async_wait(boost::asio::bind_executor(m_strand, boost::bind(&Printer::print1, this)));
			//m_timer1.async_wait(boost::bind(&Printer::print1, this));
		}
	}
	void print2()
	{
		if (m_count++ < 10)
		{
			LOG("print 2 ...count "<< m_count);
			m_timer2.expires_at(m_timer2.expires_at() + boost::posix_time::seconds(1));
			m_timer2.async_wait(boost::asio::bind_executor(m_strand, boost::bind(&Printer::print2, this)));
			//m_timer2.async_wait(boost::bind(&Printer::print2, this));
		}
	}
private:
	boost::asio::io_context::strand m_strand;
	boost::asio::deadline_timer m_timer1;
	boost::asio::deadline_timer m_timer2;
	int m_count = 0;
};
 
 
int main()
{
	boost::asio::io_context ioc;
	Printer printer(ioc);
	auto beg = boost::posix_time::second_clock::local_time();
	std::thread th([&ioc]() {
		ioc.run();
	});
	ioc.run();
	th.join();
	auto end = boost::posix_time::second_clock::local_time();
	LOG("cost " << (end - beg).total_seconds() << " (s)");
	return 0;
}
```
