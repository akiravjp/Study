print("������(1, 0)", getfenv(1), getfenv(0), getfenv(3))
--math.random
--(1)no pragram
function random_0()
	print(math.random())
end

--(2) 1 pragram
function random_1(nMax)
	local nMax = nMax
	if not nMax or nMax == 0 or nMax < 0 then
		print(math.random(nMax))
	end
	local tbRandom = {}
	for i = 1, nMax do
		tbRandom[i] = 0
	end
	
	for i = 1, 10 do 
		local nRandom = math.random(nMax)
		tbRandom[nRandom] = tbRandom[nRandom] + 1
	end
	
	for i = 1, nMax do
		print(i, tbRandom[i])
	end
	
end

-- print(math.random(1))

--random_1()
for i=1, 10 do
--print(math.random(0,5))
end
--random_1(5)
--[[
summary:
(1)û�в�������Χ��[0,1)֮���һ��С��
(2)��һ�������������ֵn(n>=1)����Χ��[1,n]
(3)��������������СֵnMin�����ֵnMax(nMax>=nMin)����Χ��[nMin,nMax]
--]]


print(math.random(8))
--ͬһ������ÿ��random��ֵ��һ��
-----------------------------

--2014/10/08 �����������

--Lib����������,ֻ֧����������� by.sunduoliang
--�ú����浵һЩbug����Ϊlua����%���㷨���⣬�ᵼ����Щ�������Զ�������浽������
Lib = {}
-- print(-5%10)
-- print(math.mod(-5, 10))
Lib.nRandomSeed = -10;
function Lib:random(nBegin, nEnd)
	local nTime = os.clock();
	self.nRandomSeed = math.floor(self.nRandomSeed or nTime);
	--print(110, self.nRandomSeed)
	self.nRandomSeed = (self.nRandomSeed * 3877 + 29573) % (4294967296);
	--self.nRandomSeed = math.mod(self.nRandomSeed * 3877 + 29573, (0xFFFFFFFF+1));
	print("nRandomSeed", self.nRandomSeed, nBegin + math.mod(self.nRandomSeed, (nEnd - nBegin + 1)))
	nBegin = nBegin or 0
	nEnd = nEnd or 65535
	if nEnd < nBegin then
		nBegin, nEnd  = nEnd, nBegin;
	end
	return nBegin + self.nRandomSeed % (nEnd - nBegin + 1)
	--return nBegin + math.mod(self.nRandomSeed, (nEnd - nBegin + 1))
end

local tbRand = {}
local tbRand1 = {}
local tbCounter = {}
g_nMaxNum = 100
g_nMaxCircle = 1000

for i=1, g_nMaxNum do
	tbCounter[i] = 0;
end

function Lib:Test()
	for i=1, g_nMaxCircle do
		--[[
		local n = Lib:random(1, g_nMaxNum)
		if i <= 10 then	
			table.insert(tbRand, n)
		end
		if i > 10 then
			for _, v in ipairs(tbRand) do
				if 
			end
		end]]
		--ͳ��
		
		local n = Lib:random(1, g_nMaxNum)
		--print(n)
		
		tbCounter[n] = tbCounter[n] + 1
	end
end

local nCount = 0;
for i=1, g_nMaxNum do
	if tbCounter[i] == 0 then
		--print(i, tbCounter[i])
		nCount = nCount + 1;
	end
end

-- print("nCount = ", nCount);
-- print((745991512 * 3877 + 29573)%0xffffffff, (745991512 * 3877 + 29573)%(0xffffffff+1))
-- print(0xFFFFFFFF, 0xffffffff+1, 0x100000000)
--[[745991512 * 3877 + 29573 = 2892209121597 (ok)
4294967295 == 0xffffffff
--(745991512 * 3877 + 29573)%0xffffffff = 
--(1)lua�����1696132062
--(2)calc�����1696132062
--(3)c++��������1696131389 = (2892209121597)%(0xffffffff+1)
]]
