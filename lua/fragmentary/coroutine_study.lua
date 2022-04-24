--coroutine
function TestCoroutineStand()
	function foo (a)
		print("foo", a)
		return coroutine.yield(2*a)
	end

	co = coroutine.create(function (a,b)
		print("co-body", a, b)
		local r = foo(a+1)
		print("co-body", r)
		local r, s = coroutine.yield(a+b, a-b)
		print("co-body", r, s)
		return b, "end"
	end)
	    
	print("main", coroutine.resume(co, 1, 10))
	print("main", coroutine.resume(co, "r"))
	print("main", coroutine.resume(co, "x", "y"))
	print("main", coroutine.resume(co, "x", "y"))
end
--[[
* resume�ķ���ֵ��bool, ...����ʽ
* �����...��Դ���������
(1)coroutine.yield��
(2)Э�����������ص�
* yield�ķ���ֵ��Դ��resume���Ĳ���
* 
]]

-- TestCoroutineStand();

-- 2014/01/17
--[[
function producer1()
	while true do
		local x = io.read()
		send(x)
	end
end

function consumer1()
	while true do
		local x = receive()
		io.write(x, "\n")
	end
end

function receive()
	return coroutine.resume(producer)
end

function send(x)
	coroutine.yield(x)
end
]]
--[[
��1��ֱ�ӵ��ú���producer1,�����������
F:\�ҵ��ļ�\data\kuaipan\work\work_diary\task\Lua_Study\code>lua coroutine_study
.lua
1
lua: attempt to yield across metamethod/C-call boundary
stack traceback:
        [C]: in function 'yield'
        coroutine_study.lua:23: in function 'send'
        coroutine_study.lua:6: in function 'producer'
        coroutine_study.lua:26: in main chunk
        [C]: ?
��2��coroutine�Ļ���ʹ��
]]

--��2������ʹ�ã�Ҫ�и������Ĺ��̣�����Ĵ����¾�Ӧ�ú�����й�ϵ��û��Эͬ�����ڰ�
--[[
co = coroutine.create(function ()
	print("Hello wrold!")
end)
print(co)
print(coroutine.status(co))
coroutine.resume(co)
print(coroutine.status(co))

co = coroutine.create(function()
	for i = 1, 10 do
		print("co", i)
		coroutine.yield()
	end
end
)
coroutine.resume(co)
print(coroutine.status(co))
coroutine.resume(co)
coroutine.resume(co)

co = coroutine.create(function(a,b,c)
	print("co", a, b, c)
end)
//coroutine.resume(co, 1, 2, 3)
coroutine.resume(co, 1, 2)

//yield�Ĳ����ᴫ��resume
co = coroutine.create(function(a, b)
	coroutine.yield(a+b, a-b)
end)

print(coroutine.resume(co, 20, 10)) //true 30 10
print(coroutine.resume(co, 20, 10)) //true��ע����û���ˣ�������û�з����κ�ְ��

//�޸�֮������
co = coroutine.create(function(a, b)
	coroutine.yield(a+b, a-b)
	return 5
end)
print(coroutine.resume(co, 10, 10)) --true 20 0
print(coroutine.resume(co, 20, 10)) --true 5

//resume�Ĳ����ᴫ��yield
co = coroutine.create(function ()
	print("co", coroutine.yield())
end)

coroutine.resume(co, 3)
coroutine.resume(co, 4, 5)
]]
--(3)��д�����ߺ�������
function TestProducer2()
	function send(x)
		coroutine.yield(x)
	end

	function receive()
		return coroutine.resume(producer)
	end

	producer = coroutine.create(function ()
		while true do
			local x = io.read()
			print("before send(yield)")
			send(x)
			print("after send(yield)")
		end
	end)

	consumer = coroutine.create(function()
		while true do
			print("before resume")
			local r, v = receive()
			if r then
				io.write(v, "\n")
				print("after resume1")
			end
			print("after resume2")
		end
	end)
	print("start............")
	coroutine.resume(producer)
	coroutine.resume(consumer)
end
-- TestProducer2();

--[[
(1)�����ߺ������߶���һ��Эͬ����
(2)����һЩ��ӡ��Ϣ����������
start............
5
before send(yield)
before resume
after send(yield)
6
before send(yield)
6
after resume1
after resume2
before resume
after send(yield)
������������мӵĴ�ӡ��Ϣ��
��1��read����������������start��ӡ֮��û�д�ӡ��Ϣ��
���ʱ�������ߺ�������û��ʼִ�У���������̻߳�û��
��2��receive������Ҳ����resume��Ҳ���������ȴ���resume��
Эͬ���򷵻أ�����yield�Ĳ����Լ�����������󷵻�ֵ��
��3��yield�����Эͬ�����̣߳������ǲ������������
���Ե�һ������5��ʱ��producer������send�ط����𣬴�ӡbefore��Ϣ
֮�����Ȼ��comsuer�̼߳���ִ���ˣ���ӡbefore֮����receive�ط�
��resume���������£�����producer�������Դ�ӡ��after send��Ȼ�����
����������ȴ�resume�ĳ���producer���أ�����producer��read�����ˣ�
�������ʱ�������ߺ������߶���������
��4�����ٴ�����6��ʱ���������ȴ�ӡbefore send��Ȼ��yield�ٶȹ��𣬲���Ϊ6��
������comsuer�յ���producer��yield����Ϊ2,��������һ�����������ڵģ���
���Ŵ�ӡreceive�е���Ϣ��������ѭ��������receive�ĵط������һ���producer��
����producer��after send��ӡ������
]]

--(4)�������͹ܵ�
--[[
function receive (prod)
	local status, value = coroutine.resume(prod)
	return value
end

function send (x)
	coroutine.yield(x)
end

function producer()
	return coroutine.create(function ()
		while true do
			local x = io.read()
			send(x)
		end
	end)
end

function filter (prod)
	return coroutine.create(function ()
		local line = 1
		while true do
			local x = receive(prod)
			x = string.format("%5d %s", line, x)
			send(x)
			line = line + 1
		end
	end)
end

function consumer (prod)
	while true do
		local x = receive(prod)
		io.write(x, "\n")
	end
end
]]
--[[
p = producer()
f = filter(p)
consumer(f)
]]

--------------------------------------
--(5)��ռcoroutine
--[[
ע������ֻ��������ķ��ͣ���û�н�������
require "luasocket"
host = "www.w3.org"
file = "/TR/REC-html32.html"
c = assert(socket.connect(host, 80))
c:send("GET" .. file .. "HTTP/1.0\r\n\r\n")
c:close()
]]

--(5.1)coroutine
function download(host, file)
	local c = assert(socket.connect(host,80))
	local nCount = 0;	--count nbyte
	c:send("GET" .. file .. "HTTP/1.0\r\n\r\n");
	
	while true do
		local s, status = receive2(c)
		nCount = nCount + string.len(s)
		if status == "closed" then break; end
	end
	
	c:close()
	print(file, nCount)
end

function receive1(connection)
	return connection:receive(2^10)
end

function receive2(connection)
	connection:timeout(0)
	local s, status = connection:receive(2^10)
	print("11111111111")
	if status == "timeout" then 
		coroutine.yield(connection)
	end
	return s, status;
end

local threads = {}

function get(host, file)
	--create coroutine
	print("22")
	local co = coroutine.create(function ()
		download(host, file)
	end)
	
	table.insert(threads, co)
end

function dispatch()
	while true do
		local n = table.getn(threads)
		if n == 0 then break; end;
		
		for i=1, n do
			local status, res = coroutine.resume(threads[i])
			if not res then
				table.remove(threads, i)
				break;
			end
		end
	end
end
--
-- print("start..............")
-- host = "www.w3.org"
-- get(host, "/TR/html401/html40.txt")
-- get(host, "/TR/2002/REC-xhtml-20020801/xhtml.pdf")
-- get(host, "/TR/REC-html32.html")
-- get(host, "/TR/2000/REC-DOM-Level-2-core-20001113/DOM2-Core.txt")
--main loop
-- dispatch()

--2015/09/02 Я���Ƿ�������
function Test()
	local co = coroutine.create(function(a, b, c)
		print("co", a, b, c)
	end)
	coroutine.resume(co, 1, 2, 3);
	print("run here ")
end

-- Test();
--

function LoadSpine()
	local function spineLoaded(id)
		print("33333333333333333333333333333", id)
		for i=1, 100 do
			print(id, i)
		end
	end
	
	local tbSpines = {
		[1] = 1001,
		[2] = 1002,
		[3] = 1003,
	}
	for _, id in pairs(tbSpines) do
		print(666, id)
		local co = coroutine.create(function(id)
			print(555, id);
			spineLoaded(id);
		end)
		coroutine.resume(co, id)
		print(777)
	end
end

-- LoadSpine();

------------------------------------------------------------------------------------------------------
local LBuildingObject = {
	
};
function LBuildingObject:_UpdateCoroutineTask(...)
    local tbFinishedIndex = {};
    for k, co in ipairs(self.m_tbCoroutineTask or {}) do
        local r, bFinished = coroutine.resume(co, ...);
		print("r, Finished = ", r, bFinished)
        if bFinished then
            table.insert(tbFinishedIndex, k);
        end
    end

    -- ɾ��������������
    for i = #tbFinishedIndex, 1, -1 do
        table.remove(self.m_tbCoroutineTask, i);
    end
end

---@function ����һ��Я�̷�װ��Task
---@param fnTask function
function LBuildingObject:_CreateCoroutineTask(fnTask, ...)
    if type(fnTask) ~= "function" then
        return;
    end

    local co = coroutine.create(function (...)
		local tbParams = {...};
		while true do
			local bFinished = fnTask(unpack(tbParams));
            tbParams = {coroutine.yield(bFinished)};
			print("bRet = ", unpack(tbParams))
		end
	end)

	print("resume...")
    local r, bFinished = coroutine.resume(co, 5);
	print("22 bFinished = ", r, bFinished)
    if not bFinished then
		self:_AddCoroutineTask(co);
    end

    return co;
end

---@param co coroutine
function LBuildingObject:_AddCoroutineTask(co)
    if not self.m_tbCoroutineTask then
        self.m_tbCoroutineTask = {};
    end

    table.insert(self.m_tbCoroutineTask, co);
end

function TestCoroutineTask()
	local co = LBuildingObject:_CreateCoroutineTask(function(a)
		print(111, a);
		return false;
	end);

	LBuildingObject:_UpdateCoroutineTask(0.5);
end

-- TestCoroutineTask();

------------------------------------------------------------------------------------------------------
--- ��֡����
local LBuildingMgr = {};
-- function LBuildingMgr:_CreateCoroutineTask1(fnTask, ...)
--     if type(fnTask) ~= "function" then
--         return;
--     end

--     local co = coroutine.create(function (...)
-- 		local tbParams = {...};
-- 		return fnTask(unpack(tbParams));
-- 	end)

--     return co;
-- end

function LBuildingMgr:_CreateCoroutineTask(fnTask, ...)
    if type(fnTask) ~= "function" then
        return;
    end

    local co = coroutine.create(function (...)
		local tbParams = {...};
		while true do
			local bFinished = fnTask(unpack(tbParams));
            tbParams = {coroutine.yield(bFinished)};
		end
	end)

    return co;
end

function LBuildingMgr:TickByCoroutine(bFrame)
	local nCount = 0;
    for nIndex, tbInfo in pairs(self.BuildingList) do
		local nBlockID, uuid = unpack(tbInfo);
		local nNum = self:TickBlockByCoroutine(nIndex, nCount, bFrame);
		nCount = nCount + nNum;
	end

	self.BuildingList = {};
	print("end. Count = ", nCount)
end

function LBuildingMgr:TickBlockByCoroutine(nIndex, nStart, bFrame)
	-- local tbDeletedBuilding = {};
	local tbBuildingInfo = self.BuildingList[nIndex];
	print("TickBlockByCoroutine = ", nBlockID, nStart, bFrame, tbBuidingList and #tbBuidingList)
	if not tbBuildingInfo then
		return 0;
	end
	local nBlockID, uuid = unpack(tbBuildingInfo);
	local nCount = 0;
	local tbParams = nil;
	-- for nIndex, uuid in ipairs (tbBuidingList) do
		-- local nBlockID, uuid = unpack(tbInfo or {});
		local sBuilding = self:GetBlockBuildingByUUID(nBlockID, uuid);
		print("111", nBlockID, uuid, sBuilding)
		if sBuilding then
			nCount = nCount + 1;
		-- else
		-- 	table.insert(tbDeletedBuilding, nIndex);
		end
		
		if bFrame and (nStart + nCount) % 2 == 0 then
			_, bFrame = coroutine.yield(false)
			print("bNewFrame = ", bFrame)
		end
	-- end

	-- print("Delete = ", #tbDeletedBuilding)
    -- for i = #tbDeletedBuilding, 1, -1 do
    --     table.remove(self.BuildingList, i);
    -- end
	
    -- coroutine.yield(true);
	return nCount;
end

function LBuildingMgr:FrameMove(fDeltaTimeInSecs)
	print("FrameMove start---------------------", fDeltaTimeInSecs)
	local r, bFinished = coroutine.resume(self.CoTick, self, true);
	print("FrameMove", r, bFinished);
	if not r then
		-- Traceback();
	end
	print(coroutine.status( self.CoTick ))
end

function LBuildingMgr:Tick(fDeltaTimeInSecs)
	print("Tick =============================================", fDeltaTimeInSecs)
	print(coroutine.resume(self.CoTick, self, false));

	-- �뿪ǰ׼������
	self.BuildingList = {};
	-- 	{1, 1},
	-- 	{1, 2},
	-- 	{1, 3},
	-- 	{2, 4},
	-- };
	for nBlockID, tbBuildings in pairs(self.m_tbBuildingList) do
		for k, v in pairs(tbBuildings) do
			self:AddFrameMoveItem(nBlockID, k);
		end
	end

	-- for nBlockID, tbBuildings in pairs(self.BuildingList) do
	-- 	for k, v in ipairs(tbBuildings) do
	-- 		print(nBlockID, v);
	-- 	end
	-- end
end

function LBuildingMgr:AddFrameMoveItem(nBlockID, uuid)
	-- if not self.BuildingList[nBlockID] then
	-- 	self.BuildingList[nBlockID] = {};
	-- end
	table.insert(self.BuildingList, {nBlockID, uuid});
end

-- function LBuildingMgr:_CheckTickCoroutineInstanceAndUpdate(bFinised)
-- 	if not bFinised and self.CoTick then
-- 		return;
-- 	end

-- 	-- �������˾����´���
-- 	self.CoTick = self:_CreateCoroutineTask(function (bFrame)
-- 		self:TickByCoroutine(bFrame);
-- 		-- xpcall(LBuildingMgr.TickByCoroutine, bFrame, debug.traceback);
-- 	end);
-- end

function LBuildingMgr:GetBlockBuildingByUUID(nBlock, nID)
    if self.m_tbBuildingList[nBlock] then
        return self.m_tbBuildingList[nBlock][nID];
    end
    return nil;
end

function TestBuildingMgrCoroutineTask()
	LBuildingMgr.m_tbBuildingList = {
		[1] = {
			[1] = 1,
			[2] = 1,
			[3] = 1,
		},
		[2] = {
			[4] = 1,
		},
		[3] = {
			[5] = 1,
		}
	}
	LBuildingMgr.BuildingList = {
		-- [nBlockID] = {uuid1, uuid2, ...}
	};
	
	LBuildingMgr.CoTick = LBuildingMgr:_CreateCoroutineTask(LBuildingMgr.TickByCoroutine, LBuildingMgr);
	-- LBuildingMgr.CoTick = LBuildingMgr:_CreateCoroutineTask(function (bFrame)
	-- 	LBuildingMgr:TickByCoroutine(bFrame);
	-- -- 	-- xpcall(LBuildingMgr.TickByCoroutine, bFrame, debug.traceback);
	-- end);

	-- LBuildingMgr:TickByCoroutine(false);
	LBuildingMgr:Tick(1);
	LBuildingMgr:FrameMove(1);
	-- table.insert(LBuildingMgr.BuildingList, {3, 5})
	-- LBuildingMgr.m_tbBuildingList[2][4] = nil;

	LBuildingMgr:FrameMove(2);
	
	-- LBuildingMgr:FrameMove(3);

	-- LBuildingMgr:FrameMove(4);

	LBuildingMgr.m_tbBuildingList[3][6] = 1;
	LBuildingMgr:AddFrameMoveItem(3, 6);
	LBuildingMgr.m_tbBuildingList[3][7] = 1;
	LBuildingMgr:AddFrameMoveItem(3, 7);
	LBuildingMgr.m_tbBuildingList[2][8] = 1;
	LBuildingMgr:AddFrameMoveItem(2, 8);

	LBuildingMgr:Tick(2);
	LBuildingMgr:FrameMove(5);
end

TestBuildingMgrCoroutineTask();