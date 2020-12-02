# nadia-proxy
是一款提供静态网页资源、后端服务反向代理的Web Service服务器。

### 功能
  * 多端口监听
    - 服务器多端口对外提供服务能力
  * 路径匹配
    - 精准路径匹配
    - 前缀路径匹配
    - 正则路径匹配
    - 无修饰符路径匹配
  * 静态代理
    - root 代理路径重定向
    - alias 代理路径重命名
  * 动态服务反向代理
    - 多主机重定向
    - 多负载均衡策略
  * 负载均衡策略
    - 轮训策略
    - 带权重轮训策略
    - IP哈希策略

### 未来功能
  * 请求域名配置&校验
  * 静态资源缓存配置&策略
  * URL哈希负载均衡策略