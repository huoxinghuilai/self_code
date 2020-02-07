启动主机节点：
./server --mode master [--port xxx] --slaver xxx.xxx.xxx.xxx [--slaver ...]

启动从几点：
./server --mode slaver --port xxx [--master xxx.xxx.xxx.xxx]

启动客户节点：
./client --dest xxx.xxx.xxx.xxx [--port xxx]

存储数据：
set （-1） key value

获取数据：
get node key (-1)

上述（-1）表示该位置的数据是不需要的，但是因为数据输入格式的问题，当前需要在该位置写入（-1）。
