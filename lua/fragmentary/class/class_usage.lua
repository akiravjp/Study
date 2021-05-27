
print(package.path);

-- require "script\\class\\class"
require "class"

--����
---@class BaseClass
BaseClass = class("Baseclass", nil);
--���캯��
function BaseClass:ctor()
   print("BaseClass:ctor");
   self.name = "Base";
end


--��������
function BaseClass:dtor()

    if self.super ~=nil then
       print("super destory");
    end

	print("BaseClass:dtor");
end


function  BaseClass:GetName()
    print("BaseClass:GetName");
    return self.name;
end




--����
---@class DerivedClass: BaseClass
DerivedClass = class("DerivedClass", BaseClass);

function DerivedClass:ctor()
    print("DerivedClass:ctor");
    self.name = "derived";
    self.age = 10;
end

function DerivedClass:dtor()  
    print("DerivedClass:dtor");  
end


function DerivedClass:GetName()
    print("DerivedClass:GetName");
    self.super:GetName();
    return self.name;
end

function DerivedClass:GetAge()
    return self.age;
end


--��һ����
---@class Worker
Worker = class("Worker");
function Worker:ctor()
    print("Worker:ctor")
    self.job = "��ũ";    
end
function Worker:dtor()
    print("Workd:dtor");
end

function Worker:Say()
    print("Worker:Say");
    print("happy coding");
end

function Worker:Build()
    print("work build");
end




--������
---@class GrandSon: DerivedClass Worker
GrandSon = class("GrandSon", DerivedClass, Worker);
function GrandSon:ctor()
    print("GrandSon:ctor");
    self.name = "john";
end

function GrandSon:dtor()
    print("GrandSon:dtor");
end

function GrandSon:Say()
    print("GrandSon:Say");
    
    --��̳������ֿ��ܻ������⣬��������ͬ���������ڸ��ǹ�ϵ�����̳�û������
    self.super:Say();

    --��̳��Ƽ��������������
    self.superByName["Worker"]:Say();
end


---@type BaseClass
base = BaseClass:new();
print(base:GetName());




collectgarbage("collect") 

--derived = DerivedClass:new();
--print(derived:GetName());

---@type GrandSon
grandson = GrandSon:new();
grandson:Say();

--grandson = nil;


print("================================");

local function gctest(self)
    print("cleaning up: ", self._name)
end

local test = {_name = "yangx"};
setmt__gc(test, {__gc = gctest})
test = nil;
collectgarbage("collect") -- ǿ����������

a = 100;


---@alias Handeler fun(type:string, data:any):void