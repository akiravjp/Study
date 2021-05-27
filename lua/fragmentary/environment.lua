--pre

--for n in pairs(_G) do print(n) end
--_G._G = _G�ڴ�ӡ������Կ���_G�����Ա
--14.1 _G

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

-- setfield("t.x.y", 10)
-- print(t.x.y, t.x)
-- print(getfield("t.x.y"), getfield("t.x"))

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
-- a=1
-- decalre "a"
-- a = 1
--]]
-------------------------------------------
--14.3
--[[
a=1
local tEnv = {}
setfenv(1, tEnv)
-- print(a)		-- error: attempt to call global 'print' (a nil value)
]]

-- 20160218
-- a = 1
-- local tEnv = {}
-- setmetatable(tEnv, {__index = _G})
-- a = 2
-- setfenv(1, tEnv)
-- print(a, _G)
-- for k, v in pairs(tEnv) do
	-- print(k, v)
-- end

------------------------------------------------------------
-- setenv
local env1 = {
	-- print = print,
}
function testSetfenv( )
	setfenv(1, env1)
	-- print("testSetfenv")	-- Error: testSetFenv�������ڵĻ�������Ϊenv1������env1��û��print������
end
-- testSetfenv()

-- local MyModel={}
-- setmetatable(MyModel, {__index = _G})
-- local func = loadfile("testSetfenv.lua")
-- print(111, func)
-- func()
-- -- �ȼ���setenv(func,MyModel);func();
-- local fenv = setfenv(func, MyModel)
-- fenv() -- �»�����û��print����
-- print("test = ", MyModel.test)
-- MyModel�����µ�ģ����������attempt to call field 'test' (a nil value)�����еĺ�����,��ʵ��lua�ڲ���model������ߺ���Ҳ���õ����ԭ��
-- print("var = ", MyModel.testvar)
-- MyModel.test()

-- @2020/06/17 setfenv loadstring���صĽ����ȷ��
function testImport(  )
	local MyModel={}
	setmetatable(MyModel, {__index = _G})
	local func = loadfile("testSetfenv.lua")

	local nType = 2
	-- not setfenv
	if nType == 1 then
		func()
		print("1 test = ", test)	-- test���еģ���Ϊ���ʱ����û������setfenv�����Ի������ǵ�ǰ�ļ�
	elseif nType == 2 then
		-- setfenv
		setfenv(func, MyModel)
		func()
		print("2 test = ", test)	-- test = nil
	elseif nType == 3 then
		local fenv = setfenv(func, MyModel)
		fenv()
		print("3 test = ", test)	-- test = nil
	end

end
testImport()
--[[
sum:
1. ע�͵�setmetatableһ��֮��print(111, func)����ִ�У���Ϊ��ǰ��������_G;����f1()��һ�䱨����Ϊ���Ļ�����ܹ���FuncEnv����FuncEnv������û��print�����ģ�����ִ��print�ᱨ��
2. ��ִ��f1()��ִ��FuncEnv.test()���Ǳ�����ʾattempt to call field 'test' (a nil value)������Ϊʲô��f1()��һ����Ҫ����һ�¾����ˣ�˵���Ѿ����µĻ����ˣ�loadfile�ǲ����е�
3. �Ӻ���testSetfenv����setfenv�ķ�Χ����������
]]

-- 2016/05/19
-- require "test_module"
-- testModule.testModule()
-- testModule()
-- print(package.loaded["test_module"])

-- local nCount = 0;
-- for k, v in pairs(package.loaded) do
	-- nCount = nCount + 1;
	-- print(nCount, k, v);
-- end

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

-------------------------------
-- @2017/12/25 lua5.3 tail call ���⣺��Ϊtail call �õ�����һ��������ջ������������getfenv(2).ENV_SCRIPT_FILE�õ��Ĳ����ǵ�ǰ�����Ļ���������д�ĺ������õ�_ENV�����Ա���[by ����]
--[[���⣺
(1)5.1��getfenv β������û��������⣿
(2)���5.3������������û�и��õĽ���취��
]]
-- 5.3���⣬��Ҫ5.3����
USE_VERSION_53 = false;
if USE_VERSION_53 then
function setfenv(fn, env)
	fn = (type(fn) == 'function' and fn or debug.getinfo(fn + 1, 'f').func)
	local i = 1
	while true do
		local name = debug.getupvalue(fn, i)
		if name == "_ENV" then
			debug.upvaluejoin(fn, i, (function()
				return env
			end), 1)
			break
		elseif not name then
			break
		end
		i = i + 1
	end
	return fn
end;

function getfenv(fn)
	fn = fn or 1;
	fn = (type(fn) == 'function' and fn or debug.getinfo(fn + 1, 'f').func)
	print("fn = ", fn)
	local i = 1
	while true do
		local name, val = debug.getupvalue(fn, i)
		if name == "_ENV" then
			print("i = ", i)
			return val
		elseif not name then
			break
		end
		i = i + 1
	end
end
end

-- a = -999
-- ����1�������
local env0 = {
	a = 0;
}
local env1 = {
	a = 1;
}
local env2 = {
	a = 2;
}
local env3 = {
	a = 3;
}
setmetatable(env0, {__index = _G})
setmetatable(env1, {__index = _G})
setmetatable(env2, {__index = _G})
setmetatable(env3, {__index = _G})

function fGetEnv0()
if USE_VERSION_53 then
	_ENV = env0;
end
	local env =  fGetEnv();
	return env;
end

function fGetEnv()
if USE_VERSION_53 then
	_ENV = env1;
end
	local env = fGetEnv1();
	return env;
end

function fGetEnv1()
if USE_VERSION_53 then
	_ENV = env2;
end
	return fGetEnv2();
end

function fGetEnv2()
if USE_VERSION_53 then
	_ENV = env3;
end
	return getfenv(2);
end

if USE_VERSION_53 then
setfenv(fGetEnv0, env0)
setfenv(fGetEnv, env1)
setfenv(fGetEnv1, env2)
setfenv(fGetEnv2, env3)
end

-- local env = fGetEnv();
-- print("env = ", env);
-- print("env = ", env.a);

-- �������2
function f1()
	local t = debug.getinfo(2);
	print(t, t.func, t.what)
	return f2()
end

function f2()
	local t = debug.getinfo(2);
	print(t, t.func, t.what)
	return f3()
	
end

function f3()
	local t = debug.getinfo(2);
	print(t, t.func, t.what)
	return 
end

-- print(getfenv(f1), debug.getinfo(2), getfenv(f2), _G, f1, f2)
print(f1, f2)
f1()


--[[
sum
(1)5.1��fGetEnv�ᱨ���������fGetEnv��ֱ�ӵ���fGetEnv2�����������ҷ��صĻ���Ҳ����ȷ��
(2)5.1�º���fGetEnv0Ҳ�ᱨ����ͺ����~
(3)�������2��5.1�汾��ȡ�ĵ�ǰ�㼶(����Ϊ1)�Ľ������ȷ�ģ���f1��f2ֵ��һ�µģ�����һ�㼶(����Ϊ2)�Ͳ�һ���ˣ����Ҳ�֪����ʲô~
(4)�������2��5.3�汾�ͱȽ�һ�£���ǰ�㼶(1)�Ľ����f1,f2������������һ�㼶(2)�Ľ����һ���ģ���������˵���������Ϊ����ļ�����Ӧ�ĺ����Ļ���_ENV
(5)���ղ������2�еĴ�ӡ��Ϣ��
* 5.1�е�ÿһ��β���ö���ռ��һ��ջ��eg:{func = nil, what = tail}��������������{func = function, what = Lua}, �ļ����ݵ���������{func = function, what = main}
��ջ��Ϣ��
function: 006AC668	function: 006AC688
table: 006AC150	function: 006AC568	main
table: 005CF738	nil	tail
table: 005CF800	nil	tail
* 5.3�е�ÿһ��β���ò���ռ��һ��ջ�ģ��������������
��ջ��Ϣ��
function: 000000000034c540	function: 000000000034c570
table: 000000000034a590	function: 000000000034eb50	main
table: 000000000034a6d0	function: 000000000034eb50	main
table: 000000000034a790	function: 000000000034eb50	main
]]



------------------------------------------------------------
