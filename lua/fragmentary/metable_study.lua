--
--pk
--2013/06/27
--

local _a1 = {20, 1, key1 = "hello", key2 = "world", lang = "lua"}
print ("the table _a1")
for _, v in pairs(_a1) do
	print (v)
end

local _a2 = {
	key1 = "hello new",
	key2 = "world new",
}

print ("\nthe old table _a2:")
for _, v in pairs(_a2) do
	print (v)
end

print("\na2��metable:", getmetatable(_a2))
print("language:", _a2["lang"])

--__index
setmetatable(_a2, {__index = _a1})

print("\nthe new table _a2:")
for _, v in pairs(_a2) do
	print (v)
end

print("\na2��metable:", getmetatable(_a2))
print ("language:", _a2["lang"])


--20131107
--gf_Inherit�����᲻�Ḳ��
--����һ��table
--orgΪԴtable��desΪ���Ƴ�������table
function gf_CopyTable(tbOrg)
    local tbSaveExitTable = {}
    local function _copy(object)
        if type(object) ~= "table" then
            return object;
        elseif tbSaveExitTable[object] then	--����Ƿ���ѭ��Ƕ�׵�table
            return tbSaveExitTable[object];
        end
        local tbNewTable = {};
        tbSaveExitTable[object] = tbNewTable;
        for index, value in pairs(object) do
            tbNewTable[_copy(index)] = _copy(value);	--Ҫ������table�����������
        end
        return setmetatable(tbNewTable, getmetatable(object));
    end
    return _copy(tbOrg);
end

--�̳�
--����tbInitInfo��Ϊ�˶Ի���ĳ�Ա���г�ʼ����Ϊ�������������³�Ա
function gf_Inherit(base,tbInitInfo)	--����һ���̳к���
	local derive = {};
	local metatable = {};
	metatable.__index = base;
	setmetatable(derive,metatable);
	for i,v in pairs(base) do
		if type(v) == "table" then
			derive[i] = gf_CopyTable(v);
		end;
	end;
	if tbInitInfo then	--���Ҫ�ı����ĳ�Ա�������µĳ�Ա
		for i,v in pairs(tbInitInfo) do
			derive[i] = v;
		end;
	end;
	return derive;
end;

tbSrc = {
	[1] = 5,
	[2] = 7,
	src1 = 1,
	src2 = 2,
	tbSrc1 = {2, 3}
}

tbSrc2 = {
	[1] = 6,
	src3 = 3,
	9,
}

function TestInherit(base, tbInitInfo)
	local derive = {};
	local metatable = {};
	metatable.__index = base;
	setmetatable(derive,metatable);
	for i,v in pairs(base) do
		if type(v) == "table" then
			derive[i] = gf_CopyTable(v);
		end;
	end;
	if tbInitInfo then	--���Ҫ�ı����ĳ�Ա�������µĳ�Ա
		for i,v in pairs(tbInitInfo) do
			derive[i] = v;
		end;
	end;
	return derive;
end

local tbTest = gf_Inherit(tbSrc, tbSrc2)
print("..........")
for i, v in pairs(tbSrc) do
	print(i, v)
end
print("..........")
for i, v in pairs(tbSrc2) do
	print(i, v)
end
print("..........")
for i, v in pairs(tbTest) do
	print(i, v)
end
print(tbTest[1], tbTest[2], tbTest.src1, tbTest.src2)

--------------------------------------------------------
--(1.1)__index
print(1.1)
Window = {}
Window.prototype = {x = 0, y = 0, width = 100, height = 100, }
Window.mt = {}
function Window.new(o)
	setmetatable(o, Window.mt)
	return o;
end

Window.mt.__index = function ( table, key)
	return Window.prototype[key]
end

w = Window.new{x=10, y = 20}
print(w.width)

--(1.2) __newindex
--[[
function setDefault(t, d)
	local mt = {__index = function() return d end}
	setmetatable(t, mt)
end

local mt = {__index = function (t) return t.___ end}
function setDefault(t, d)
	t.___ = d
	setmetatable(t, mt)
end
]]

local key = {}
local mt = {__index = function (t) return t[key] end}
function setDefault(t, d)
	t[key] = d
	setmetatable(t, mt)
end

tab = {x = 10, y = 20}
print(tab.x, tab.z)

setDefault(tab, 0)
print(tab.x, tab.z)

tab1 = {x = 15, y = 25}
setDefault(tab1, 1)
print(tab.x, tab.z, tab1.x, tab1.z)
--[[
ע������ֱ����table����key���������Ϊkey��tableʵ���Ͼ���һ����ַ
(eg:0x0000ABCD)
���Կ��Ե���key������Ҳ��Ψһ��
������ϸ��һ��table�Ľṹ���Ծ��ò��ף��Ͼ���������table�Ĵ洢�ṹ��С
]]

--��1.3����ر�
--��ʵ������������ֵ֮�����һ������ʵ��ʹ��index��newindexʵ��

t = {}

--[[local _t = t
t = {}
local mt = {
	__index = function(t, k)
	print("*access to element " .. tostring(k))
	return _t[k]
	end,
	
	__newindex = function(t, k, v)
	print("*update of element " .. tostring(k) ..
		" to " .. tostring(v))
	_t[k] = v
	end

}
setmetatable(t, mt)]]

--˽��key
local index = {} --��table��key��ͬ1.2�еġ�ע��
local mt = {
	__index = function(t, k)
	print("*access to element " .. tostring(k))
	return t[index][k]
	end,
	
	__newindex = function(t, k, v)
	print("*update of element " .. tostring(k) ..
		" to " .. tostring(v))
	t[index][k] = v
	end
}	
function track(t)
	local proxy = {} --ÿ����һ��track����������һ���µ�proxy
	proxy[index] = t
	setmetatable(proxy, mt)
	return proxy
end

t = track(t)
--t[2] = 'hello'
--print(t[2])
--print(t[1])

t1 = track(t)
print(t1[3])
--[[
^_^
�����ӡ������
*access to element 3
*access to element 3
��Ϊ�����õ���t������һ��track���ģ�����t1��track�����εģ�����
^_^
]]
--print(t[2])

------------
--(1.4)ֻ����
function readOnly(t)
	local proxy = {}
	local mt = {
		__index = t,
		__newindex = function (t, k, v)
			error("attempt to update a read-only table", 2)
		end
	}
	
	setmetatable(proxy, mt)
	return proxy;
end

days = readOnly{"Sunday", "Monday", "Tuesday", "Wednesday",
	"Thursday", "Friday", "Saturday"
}

for k, v in pairs(days) do
	print("metatable", k, v);
end

print(days[1])
-- days[2] = "Noday"
print(days[2])

--sum:
--(1)Ԫ�������pairs��ȡ����
--(2)ֱ��__newindex��û��Ч����


----------------------------------
--2015��07��07 ������
--���⣺���߶ദ��ʹ�ã���������е��߱�ɾ����Ҫɾ���ô����߶���
print("Test ������ ...................................")
local tbItem1 = {1, 3};
local tbItem2 = {2, 2};
local tbItem3 = {3, 5};
local tbItems = {
	[1] = tbItem1,
	[2] = tbItem2,
	[3] = tbItem3,
}
local tbWeak = {
	[1] = tbItems[1]
}

setmetatable(tbWeak, {__mode = "v"});
print("before:");
for k, v in pairs(tbWeak) do
	print(k, v)
end
tbItem1 = nil;
tbItems[1] = nil;
collectgarbage();
print("after:");
for k, v in pairs(tbWeak) do
	print(k, v)
end
print("...........................end..............................")