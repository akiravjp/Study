

-------------------------------------------------------------
--lua������󣺼򵥴ֱ���ʵ��
function copytable(tbArg)
	local tbCollsion = {}
	
	--local������������
	local copy	
	copy = function (obj)
		if type(obj) ~= "table" then
			return obj;
		end
		--����Ƿ���Ƕ��ѭ����table
		if tbCollsion[obj] then
			return tbCollsion[obj];
		end
		
		local tbNew = {}
		tbCollsion[obj] = tbNew;
		--�ݹ鸴��
		for k, v in pairs(obj) do
			tbNew[k] = copy(v);
		end
		--������֮��Ԫ���ϵҲҪ��������
		return setmetatable(tbNew, getmetatable(obj))
	end

	return copy(tbArg);
end

function inherit(tbBase, tbClass)
	--���ƻ���
	local tbNew = copytable(tbBase)
	
	
	local tm = {}
	tm.__index = tbClass;
	setmetatable(tbNew, tm)
	
	--�޸�tbBaseΪtbClass�еĳ�Ա����������tbClass�еĳ�Ա
	if tbClass then
		for k, v in pairs(tbClass) do
			tbNew[k] = v
		end
	end

	return tbNew;
end
--ʹ��
local tbObject = {}
local tbFruit = inherit(tbObject)
local tbApple = inherit(tbFruit)
local tbBanana = inherit(tbFruit)
local tbBanana1 = inherit(tbFruit)
local tbBanana2 = inherit(tbFruit, tbBanana1)


--lua������󣺸��������ϵ�ʵ��
local _class={}
 
function class(super)
	local class_type={}
	--ע�⣺��Ϊ������__newindex����, ����ctor��Ҫ����Ϊnil
	class_type.ctor=false
	class_type.super=super
	class_type.new=function(...) 
			local obj={}
			--����Ŀ�ֻ����һ���£����δӸ��ൽ��ǰ������ù��캯��ctor
			do
				local create
				create = function(c,...)
					if c.super then
						create(c.super,...)
					end
					if c.ctor then
						c.ctor(obj,...)
					end
				end
 
				create(class_type,...)
			end
			setmetatable(obj,{ __index=_class[class_type] })
			return obj
		end
	
	--�¼ӳ�Ա����ֹ��������ú���
	local vtbl={}
	_class[class_type]=vtbl
 
	setmetatable(class_type,{__newindex=
		function(t,k,v)
			vtbl[k]=v
		end
	})
 
	--ֻ�ж������޸���__newindex
	--vbtlֻ���ڶ�����
	--new�����Ķ��������ж���������ã��������Լ������ӵĳ�Ա����
	if super then
		setmetatable(vtbl,{__index=
			function(t,k)
				local ret=_class[super][k]
				vtbl[k]=ret
				return ret
			end
		})
	end
 
	return class_type
end


--test
--Ƕ��table
local tbCircle1 = {
	[1] = 2,
	[2] = tbCircle2,
}

local tbCircle2 = {
	[1] = 2,
	[2] = tbCircle1,
}
tbCircle1[2] = tbCircle2

local tbCircle3 = inherit(tbCircle2, {[1] = 3, [4] = "test"})

print("tbCircle1", tbCircle1)
for k, v in pairs(tbCircle1) do
	print(k, v)
	if type(v) == "table" then
		for k1, v1 in pairs(v) do
			print("\t", k1, v1)
		end
	end
end

print("tbCircle2", tbCircle2)
for k, v in pairs(tbCircle2) do
	print(k, v)
	if type(v) == "table" then
		for k1, v1 in pairs(v) do
			print("\t", k1, v1)
		end
	end
end

print("tbCircle3", tbCircle3)
for k, v in pairs(tbCircle3) do
	print(k, v)
	if type(v) == "table" then
		for k1, v1 in pairs(v) do
			print("\t", k1, v1)
		end
	end
end

for i=1, 4 do
	print(tbCircle3[i])
end
-------------------------------------------------------------------------

-- 2. table�ĳ���
