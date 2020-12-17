var context;
var map;
// 初始化
function initqt()
{
if (typeof qt != 'undefined')
{
new QWebChannel(qt.webChannelTransport, function(channel)
{
			context = channel.objects.context;
}
);
}
else
{
alert("qt对象获取失败！");
}
}
// 向qt发送消息
function sendMessage(msg)
{
if(typeof context == 'undefined')
{
alert("context对象获取失败！");
}
else
{
context.onMsg(msg);
}
}
// 控件控制函数
function onBtnSendMsg()
{
var cmd = document.getElementById("待发送消息").value;
sendMessage(cmd);   
}
initqt();
// 接收qt发送的消息
function recvMessage(msg)
{
alert("接收到Qt发送的消息：" + msg);
}
$(document).ready(function(){
	map = new AMap.Map('container', 
	{
		resizeEnable: true, //是否监控地图容器尺寸变化
		zoom:11, //初始化地图层级
		center: [116.397428, 39.90923] //初始化地图中心点
	});
});
