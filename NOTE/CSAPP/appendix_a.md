# APPENDIX A - Error Handling



- `Unix-Style Error Handling` Functions such as **fork** that **wait** that were developed in the early days of Unix(as well as some older Posix functions) overload the function return value with both error codes and useful results.
- `Posix-Style Error Handling` Many of the newer POSIX functions such as Pthreads use the return value only to indicate success(zero) or failure(nonzero). Any useful results are returned in function arguments that are passed by reference.
- `GAI-Style Error Handling` The **getaddrinfo** (GAI) and **getnameinfo** functions return zero on success and a nonzero value on failure.



## Glossary

<div style="width: 50%; float:left;">reluctant `/rɪˈlʌktənt/` 勉强的，不情愿的</div>
<div style="width: 50%; float:left;">clutter `/'klʌtə(r)/` 弄乱，混乱，杂乱</div>
<div style="width: 50%; float:left;">indicate `/ˈɪndɪkeɪt/` 指示，说明，象征，显示，预示</div>
<div style="width: 50%; float:left;">concise `/kən'saɪs/` 简明的，简要的</div>