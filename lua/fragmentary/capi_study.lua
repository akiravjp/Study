--����ƪCAPI
----------------------------
--26
--(1)internet
--��http://www.cnblogs.com/stephen-liu74/archive/2012/07/23/2469902.html��
--require "mystudylib"  --ָ��������

--�ڵ���ʱ��������package.function
--print(mystudylib.add(1.0,2.0))
--print(mystudylib.sub(20.1,19))

--(2)��Programming in Lua��
--mylib = loadlib("mylib", "luaopen_mylib")
--ע�����а���
----------------------------
--27
--27.1
--[[
function Encode(nNumber)
	return nNumber+3
end
local tbTest = {1, 2, 3}
print(unpack(tbTest))
mystudylib.map(tbTest, Encode)
print(unpack(tbTest))
]]

--27.2 string
--[[
local tbSplit = mystudylib.split("hi,,there", ",")
print(tbSplit)
for _, v in pairs(tbSplit) do
	print(v)
end
]]
--[[
summary:��������Կ���lua����c����������ֵ�ǵ�ǰջ�������Ԫ�أ�������Ҫ����ʲô�������Լ�ʲô���ݣ��㸺���ٵ��ø�cpi֮��ջ������������Ҫ���ص����ݼ��ɡ�
]]

--27.3 closure
--[[
local counter = mystudylib.newCounter()
for i=1, 5 do
	print(counter());
end
]]

------------------------------------------------------------
--28
--package.loadlib("mystudylib", "luaopen_mystudylib")()   --ָ��������
--print(mystudylib.add(1.0,2.0))
--����һ�ֵ���c��̬��ķ�ʽ
--package.loadlib("mystudylib", "luaopen_mystudylib")()
--print(mystudylib.add(1.0,2.0))

--28.1
--package.loadlib("array", "luaopen_array")()
--����lua: capi_study.lua:57: attempt to call a nil value
--[[
����������½�һ�����̣����ֽ���array��������dll��Ϊarray.dll��
�ܽ᣺���溯��(package.loadlib)�ĵ�һ���������յ��ַ�����dll����Ҫһ��������ȥ����Դ���룬����ν����ġ�
]]
--[[
a = array.new(1000)
print(a)
print(array.size(a))
for i=1, 1000 do 
	array.set(a, i, 1/i)
end
print(array.get(a, 10))
--success
]]

--28.2
--package.loadlib("array", "luaopen_array")()
--a = array.new(1000)
--print(a)
--print(array.size(a))

--28.3
--[[
a = array.new(1000)
print(a:size())
a:set(10, 3.4)
print(a:get(10))
--fail
]]
--[[
�ܽ᣺
1.ֱ����28.2��dll�ǲ��еģ���Ҫ����__indexԪ����
]]
--require "array"
--package.loadlib("array", "luaopen_array")()
--a = array.new(1000)
--print(a:size())
--a:set(10, 3.4)
--print(a:get(10))
--fail
--[[
�ܽ᣺
1. ����ͨ��ȥ���ϲ����ϸ������programming in lua���е�luaL_openlib����Ϊʲôû���˵����ݣ�������һ��ԭ�����Ǻ������ˣ� ʹ���µĺ����ӿں�ʹ�÷�ʽȥע�ắ��
2. ��������ȥ���������ϣ������Լ��İ汾��5.1��ֱ����document�е�5.1��reference manual���е�7.3�п�����Changes in  API���������˷ǳ��ʺ��Լ��Ľ��ͣ�luaL_open�ӿڲ����ˣ��޸ĳ���luaL_register�ˣ����Һ�luaL_openlibһ��Ҳ֧�ֵڶ���������package������ΪNULL����ô���ǰѵ�ǰ����������luaL_Reg�еĺ���ע�ᵽ��ǰջ������ı��У������������ʹ�õĻ������Լ�Ҫ��֤���������һ��table������������Ҫ�Ľ�������ţ�
��http://www.lua.org/manual/5.1/manual.html#7.3��
3. a:size���ǲ���
]]
--[[
print(a.size)
print(getmetatable(a))
--print(a.size(a))
--print(a:size()) --lua: capi_study.lua:102: calling 'size' on bad self (luaBook.array expected, got userdata)
print(getmetatable(a).__index.size)
print(getmetatable(a).__index)
--print(getmetatable(a).__index.size())	--error as before
print(a:size())
]]
--fail

-- package.loadlib("array", "luaopen_array")()
-- a = array.new(1000)
-- print(a:size())
-- a:set(10, 3.4)
-- print(a:get(10))

--2014/03/24
--[[
�ܽ᣺
1. �ӵ���������֪��ԭ���������ˣ�����void *ud = luaL_checkudata(L, 1, "LuaBook.array");�е�"LuaBook.array"д����"luaBook.array"
]]

--------------------------------------------------------
--29.1
--linux
--[[
(1)luaL_Regд����luaL_reg��ʾ�� ����������Ԫ�ص����Ͳ���ȫ��
�����ϣ���gcc4����ʱ��������Ԫ�ص����Ͳ���ȫ����������Ϊgcc4����������������ǰʹ�á� ��http://blog.csdn.net/horsefaced/article/details/1678965��
	ͣ����ȥ˼��һ�¿��Է����������ڱ����ʱ��û�з�������ṹ��Ķ��壬��Ϊ���¶���ģ��ͻᱨ�����Ĵ�������ṹ����ǰ���ͷ�ļ����Ƕ����˵ģ���˵����Ľṹ��д���ˣ��Ժ������˼������������
�����luaL_reg�ĳ�luaL_Reg����
(2)linux���滹��ʹ��luaL_openlib,ʹ��luaL_register���ɹ�
window�µ�lua�İ汾��5.1
linux�µ�lua�汾��5.2.0����Ҫ��������
----
�ֲ���˵���������luaL_registerȡ����luaL_register��Դ���еĶ��壺
#define luaL_register(L,n,l) (luaL_openlib(L,(n),(l),0))
---
��http://blog.csdn.net/ym012/article/details/7188707��

(3)linux���涯̬�����
���gcc mylib.c -fPIC -shared -o libmylib.so

(4)������
mydir.c:18: ���棺���ݲ��� 2 (���� ��lua_getmetatable��)ʱ��ָ�븳��������δ������ת��
ԭ�򣺴���������
* luaL_getmetatableд����lua_getmetatable������һ����д��L
* lua_setmetatableд����lus_setmetatable�������Ȼ�������õ�

�����������ˣ����붯̬���ļ�mydir.soû�б���ok

(5)linux����ʹ�ö�̬��
*ִ��Lua���뽻��ģʽ
* package.loadlib("./libmydir.so", "luaopen_mydir")()--�򿪿�
* for fname in mydir.mydir(".") do print(fname) end
ע��
*����û��ֱ����dir����Ϊ�����°�dirע���ȫ�ֺ��������һ���ʹ�������ע���һ�������ʽ
/*static const struct luaL_Reg mydir[] = {
        {"mydir", l_dir},
        {NULL, NULL},
};*/

//int luaopen_mydir (lua_State *L){
//      luaL_newmetatable(L, "LuaBook.dir");

        /* set its __Gc field */
//      lua_pushstring(L, "__gc");
//      lua_pushcfunction(L, dir_gc);
//      lua_settable(L, -3);

        /* register the 'dir' function */
//      lua_pushcfunction(L, l_dir);
//      lua_setglobal(L, "dir");
//      luaL_openlib(L, "mydir", mydir, 0);

//      return 0;
//}
*�ĳ����ϵ���ʽ��ֱ��ע���ȫ�ֺ���Ҳ�ǿ���ide
int luaopen_mydir (lua_State *L){
        luaL_newmetatable(L, "LuaBook.dir");

        /* set its __Gc field */
        lua_pushstring(L, "__gc");
        lua_pushcfunction(L, dir_gc);
        lua_settable(L, -3);

        /* register the 'dir' function */
        lua_pushcfunction(L, l_dir);
        lua_setglobal(L, "dir");

        return 0;
}
]]
------------------------------------------------------------------------------------------------------
-- require "mystudylib"  --ָ��������
--[[ ����
        error loading module 'mystudylib' from file '.\mystudylib.dll':
        Ӧ�ó����޷���������ΪӦ�ó���Ĳ������ò���ȷ���й���ϸ��Ϣ�������Ӧ�ó����¼���־����ʹ�������� sxstrace.exe ���ߡ�
]]
-- package.loadlib("mystudylib", "luaopen_mystudylib")()
-- print(mystudylib.add(1.0,2.0))