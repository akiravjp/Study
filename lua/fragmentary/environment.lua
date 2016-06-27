--pre

--for n in pairs(_G) do print(n) end
--_G._G = _G�ڴ�ӡ������Կ���_G�����Ա
--14.1 _G
--[[
function getfield(f)
	local v = _G
	for w in string.gfind(f, "[%w_]+") do
		v = v[w]
	end
	return v
end

function setfield(f, v)
	local t = _G
	for w, d in string.gfind(f, "([%w_]+)(.?)") do
		if d == "." then
			t[w] = t[w] or {}
			t = t[w]
		else
			t[w] = v
		end
	end
end

setfield("t.x.y", 10)
print(t.x.y, t.x)
print(getfield("t.x.y"), getfield("t.x"))
]]

--------------------------------------
--14.2
--[[
function decalre(name, initval)
	rawset(_G, name, initval or false)
end

setmetatable(_G, {
	__newindex = function (_, n)
		error("attempt to write to undeclared variable " .. n, 2)
	end,
	__index = function(_, n)
		error("attempt to read undeclared variable " ..n, 2)
	end
})
--a=1
decalre "a"
a = 1
]]

-------------------------------------------
--14.3
--[[
a=1
local tEnv = {}
setfenv(1, tEnv)
-- print(a)		-- error: attempt to call global 'print' (a nil value)
]]

-- 20160218
a = 1
local tEnv = {}
setmetatable(tEnv, {__index = _G})
a = 2
setfenv(1, tEnv)
-- print(a, _G)
for k, v in pairs(tEnv) do
	print(k, v)
end

------------------------------------------------------------
-- setenv
local env1 = {
	-- print = print,
}
function testSetfenv( )
	-- block
	if true then
		setfenv(1, env1)
		-- print("111111111")
	end
	-- print("22222")
end
testSetfenv()

local FuncEnv={}
-- setmetatable(FuncEnv, {__index = _G})
local func = loadfile("testSetfenv.lua")
print(111, func)
func()
--�ȼ���setenv(func,FuncEnv);func();
local f1 = setfenv(func,FuncEnv)
f1()
print(222, f1, FuncEnv.test)
--FuncEnv�����µ�ģ����������attempt to call field 'test' (a nil value)�����еĺ�����,��ʵ��lua�ڲ���model������ߺ���Ҳ���õ����ԭ��
-- FuncEnv.test()
print(FuncEnv.testvar)

--[[
sum:
1. ע�͵�setmetatableһ��֮��print(111, func)����ִ�У���Ϊ��ǰ��������_G;����f1()��һ�䱨����Ϊ���Ļ�����ܹ���FuncEnv����FuncEnv������û��print�����ģ�����ִ��print�ᱨ��
2. ��ִ��f1()��ִ��FuncEnv.test()���Ǳ�����ʾattempt to call field 'test' (a nil value)������Ϊʲô��f1()��һ����Ҫ����һ�¾����ˣ�˵���Ѿ����µĻ����ˣ�loadfile�ǲ����е�
3. �Ӻ���testSetfenv����setfenv�ķ�Χ����������
]]

-- 2016/05/19
require "test_module"
-- testModule.testModule()
-- testModule()
-- print(package.loaded["test_module"])

local nCount = 0;
for k, v in pairs(package.loaded) do
	nCount = nCount + 1;
	print(nCount, k, v);
end

-- code1:
-- require "test_module"
-- testModule.testModule()

-- code2:
-- a = require "test_module"
-- a.testModule()

--[[
sum:
1. module��package.seeall������ģ�飬���Ҹ�ģ���ܹ�����_G
2. module�ĵ�һ��������ģ������
eg: ��code1��ʾ�Ϳ��Ե���ģ���е�����
3. module��һ������������ַ���"..."Ҳ���ԣ����Կ���package.loaded����һ��...�ı�
eg: ֻ��ͨ�����ַ�ʽ���ã�package.loaded["..."].testModule(),Ҳ����ͨ��code2�ķ�ʽ����
4. module��һ�����������...Ҳ�ǿ��Եģ�����ͨ��code2�ֵķ�ʽ���ʣ���Ϊ���ʱ��֪������
5. module��һ�����������nil, ����bad argument #1 to 'module' (string expected, got nil)
]]