--
-- pk@ 2012-07-23
--

--------------------------------------------------------------
--1.pairs result
local tbTestPairs ={
	[1] = 1,
	nTest_1 = 2,
	szTest = "test",
	tbTest = {},
	nTest_2,
}
local a1 = 5
local tbTestPairs1 = {1, a= 2, 3, a1, "string",}
for k, v in pairs(tbTestPairs1) do
	--print (k, v)
end
--summary:
--[[
	(1)paris�����
	(2)�������nTest_2��a1��û�д�ӡ����
	(3)k��ֵ��һ������number��keyֵ����table�����趨��keyֵ�����keyֵû�о������֣�Ĭ����1��ʼ
	(4)��a1��ֵ֮�󣬾��ܹ���ӡ������keyֵΪ4
]]


--------------------------------------------------------------
--[[
--2.string.format(%s, number)
local szStringFormat = string.format("string-fromat:%s", 5234111)
print(szStringFormat)

--3.mod return 0?
--print(5%2)

--print((1851+24*3600)%(24*3600))

print(113461870%(31*24*3600) / 2678400)
print(113461870%(30*24*3600) / (30*24*3600))

--
print(50/100)

tbT1 = {
	[2] = 2;
}
print("#tbT1", #tbT1)

print(6%1)

print(string.format("%2d", 1))
]]
---------------------------
--tableֱ�Ӹ�ֵ����ʵ������
--[[
tbRaw = {
	[1] = 2,
	[2] = 3,
	[3] = {"x", "y"},
	[4] = {"x1", "y1"},
}

tbRaw1 = {}
tbRaw1[1] = tbRaw[1]
tbRaw1[2] = tbRaw[2]
tbRaw1[3] = tbRaw[3]
table.insert(tbRaw1, tbRaw[4])
tbRaw1[1] = 6
tbRaw1[3][2] = "z"
tbRaw1[4][2] = "z1"

local nRaw1 = tbRaw[1]
print(nRaw1, tbRaw[1], tbRaw[3][2], tbRaw[4][2], tbRaw1[1], tbRaw1[3][2], tbRaw1[4][2])
nRaw1 = 5
print(nRaw1, tbRaw[1], tbRaw1[1])
]]
---------------------------------------
--[[
local tbRemoveTest = {
	[1] = "x",
	[5] = "y",
	[1000] = "z",
}
for k, v in pairs(tbRemoveTest) do
	print(k, v)
end
table.remove(tbRemoveTest, 5)
for k, v in pairs(tbRemoveTest) do
	print(k, v)
end
--]]
--ע��removeֻɾ�����鲿�֣�������ֱ��remove��ϣ�����ǲ��ɹ���
--[[
table.remove()����ɾ��������table���鲿��λ��posλ�õ�Ԫ��. ����Ԫ�ػᱻǰ��. pos������ѡ, Ĭ��Ϊtable����, �������һ��Ԫ��ɾ��.
]]
-----------------------------------------------
--2014/03/21 ����˯����
--�������Ǹ�����
--[[
math.randomseed(os.time())
for i=1, 5 do
print(math.random(-5, 3))
end

local i = 3
if i > 1 then
	print("111")
elseif i > 2 then		
	print("222")
end
]]
--local szTest = "12"
--print(math.fmod(szTest, 10))

--[[
local szSql = "delete from %s"
szSql = string.format(szSql, "abc")
print(1, szSql)
szSql = string.format(szSql, "def");
print(2, szSql)


--2014/09/25
--lua�����ܴ�64λ����
local nNum = 359802307978703
print(nNum)
print(nNum == 359802307978703, 359802307978703/100000)
print(math.mod(5, 10), math.mod(-2, 10), -2%10)
print(5%10, -2%10, math.mod(5.5, 10), 5.5%10)
]]
--[[
(1)֧��64λ
(2)���ǻ����и����⣬��������03��������
���ο���http://www.cnitblog.com/Richmond/archive/2011/03/09/73040.html��
]]

--[[
--2015/01/23
--local���÷��ͷ�Χ
--���������_Gһ��������ǰ�ļ����������local����
for k, v in pairs(_G) do
	--print(k, v)
end
local tbEnv = getfenv()
-- print("..................", tbEnv, _G)
for k, v in pairs(tbEnv) do
	--print(k, v)
end
-- print("a", a)
local a = 5
-- print("a", a)
local fLocal
fLocal = function(n)
	if (n == 1) then
		return n;
	else
		return n + fLocal(n-1)
	end
end
-- print("result:", fLocal(2))

--2015/01/25
tbClass = {
	f1 = nil,
	f2 = false,
}
for k, v in pairs(tbClass) do
	print(k, v)
end
setmetatable(tbClass, {__newindex = 
	function(t, k, v)
		
	end
})

function tbClass:f1()
	print("f1")
end

function tbClass:f2()
	print("f2")
end
-- print("result:", tbClass.f1, tbClass.f2)
-- tbClass:f1()
-- tbClass:f2()

--2015/01/27
fCo = function (id)
		local tLast = os.time();
		while true do
			local tNow = os.time()
			if math.abs(tLast - tNow) >= 10 then
				print(id, tNow)
			else
				print(id, tNow)
			end
		end
end
-- for i=1, 1000 do
	-- local co = coroutine.create(fCo)
	-- coroutine.resume(co, i)
	-- print("111111111111111111")
	-- coroutine.yield()
-- end

--2015/01/31 
-- for k, v in pairs(_G) do
	-- print(k, v)
-- end
]]

--[[
--2015/03/13
-- local n = math.random()
-- print(n, math.random(1))

--2015/03/14
-- print("10^0�� ", 10^0)

--2015/03/17
-- print(string.format("%s", tostring(false)))

--2015/03/19 
local tbIndex = {}
for i=0, 3 do
	tbIndex[i] = i;
end
for k,v in ipairs(tbIndex) do
	print (k, v)
end
]]

--------------------------------------------
--����nλС������
local a = 1000.11123423523 % 0.1
local b = 1000.11123423523 - a;
-- print(a, b)
-- print(111)
--2015/06/25 gf_GetPreciseDecimal(0.25)�����һ��
function gf_GetPreciseDecimal_1(nNum, n)
	if type(nNum) ~= "number" then
		return nNum;
	end
	
	n = n or 0;
	n = math.floor(n)
	local fmt = '%.' .. n .. 'f'
	local s = string.sub(tostring(nNum), 1, 5)
	print(222, s)
	print(111, fmt, string.format(fmt, nNum))
	local nRet = tonumber(string.format(fmt, nNum))

	return nRet;
end
-- print("1. GetPreciseDecimal(0.38461538461538) = ", gf_GetPreciseDecimal_1(0.38461538461538, 1))

-- print("�ӣ�", 0.5 % 0.1, 0.7 % 0.1, 0.6 % 0.1, 0.8 % 0.1)
--@function: ����nλС��
function gf_GetPreciseDecimal_2(nNum, n)
	if type(nNum) ~= "number" then
		return nNum;
	end
	n = n or 0;
	n = math.floor(n)
	if n < 0 then
		n = 0;
	end
	local nDecimal = 1/(10 ^ n)
	if nDecimal == 1 then
		nDecimal = nNum;
	end
	local nLeft = nNum % nDecimal;
	return nNum - nLeft;
end
-- print("2. GetPreciseDecimal(0.7) = ", gf_GetPreciseDecimal_2(0.7, 1))

function gf_GetPreciseDecimal_3(nNum, n)
	if type(nNum) ~= "number" then
		return nNum;
	end
	n = n or 0;
	n = math.floor(n)
	if n < 0 then
		n = 0;
	end
	local nDecimal = 10 ^ n
	local nTemp = math.floor(nNum * nDecimal);
	local nRet = nTemp / nDecimal;
	return nRet;
end
-- print("3. GetPreciseDecimal(0.38461538461538) = ", gf_GetPreciseDecimal_3(0.7, 1))
-- print("3. GetPreciseDecimal(0.7) = ", gf_GetPreciseDecimal_3(0.7, 1))
-- print(0.6 %0.1, 0.5%0.1, 0.7%0.1, 0.8%0.1)
--[[
sum:
(1)
]]
--------------------------------------------
--2015��07��07 ��������Ŀ2
function compute()
	for i=1,9 do
		local tbRet = {}
		local tbTemp = {1, 2, 3, 4, 5, 6, 7, 8, 9}
		tbRet[1] = tbTemp[i];
		table.remove(tbTemp, i);
		for i = 1, #tbTemp do
			tbRet[2] = tbTemp[i]
			local x1 = tbRet[1] * 10 + tbRet[2]
			if x1 < 100 then
				table.remove(tbTemp, i);
				for i=1, #tbTemp do
					print(222, x1, i, tbTemp[i])
					local x2 = x1 * tbTemp[i];
					if x2 < 100 then
						tbRet[3] = tbTemp[i]
						table.remove(tbTemp, i);
						local x4 = math.floor(x2 / 10)
						local x5 = x2 % 10
						--check
						local bTrue = true;
						for _, v in pairs(tbRet) do
							if v == x4 or v == x5 then
								bTrue = false;
								break;
							end
						end
						-- for _, v in pairs(
						if bTrue then
							tbRet[4] = x4;
							tbRet[5] = x5;
							print(111, tbRet[1] .. tbRet[2] .. " * " .. tbRet[3] .. " = " .. tbRet[4] .. tbRet[5])
						end
						--check end
					end
				end
			end
		end
	end
end

-- compute()

-------------------------------
--2015��08��03 print��buf̫С��(CCConsole.h)
local szLog = [[
	1234567
	abcdefg
]]

function long_print(szLog)
	local nStart, nEnd = 1;
	local nMax = 10;
	local nLong = #szLog;
	while true do
		local nEnd = nStart+nMax-1
		if nEnd > nLong then
			nEnd = -1;
		end
		local szTemp = string.sub(szLog, nStart, nEnd);
		print(nStart, nEnd, szTemp)
		nStart = nMax + 1;
		if nEnd == -1 then
			break;
		end
	end
end
-- long_print(szLog);


-- 2015/08/15 ֱ���ÿ� 
local tbDt = {
[1] = 3,
[2] = 5,
[3] = 4,
}
-- print(#tbDt)
-- tbDt[2] = nil;
-- print(#tbDt)

-- 2015/08/15
-- print(math.ldexp(2.0,0.1))

-- for i=0 ,1, 0.2 do
	-- local nExp = math.exp(i);
	-- local nExp2 = 2^i;
	-- print(nExp, nExp2);
-- end

-- 2015/09/01 ʱ�亯��
local a, b = os.time(), os.clock()
-- print(a, b)
--[[
sum:
1. ����os.clock����ִ�иó���CPU��ȥ��ʱ��������Ҳ��������ļ�һֱִ�еĻ���a��ֵ��һֱ�����ӣ���Ϊ����ڵ���ʼ��һֱû��(1970��1��1��), ����b��ֵ�ں�С�ķ�Χһֱ����(0.001~0.003��)
]]

-- 2015/12/17 print ����
local printSave = print;
local _nonprint = function ()
end
-- print = _nonprint
-- print("33333333333");
-- print = printSave;
print("111111111111111111111111111111111111111111111");
printSave("2222222222222222222222222222222222222");