-- require study
-- page@2015/04/25
--------------------------------------------------------
--1. 
--------------------------------------------------------
local mRandom = require("random")
print (mRandom)

print(package.path)

function TestPrintPackageLoaded()
	print(getfenv(1), _env)
	for k, v in pairs(package.loaded) do
		print (k, v)
	end
end

print(getfenv(1), getfenv(0), getfenv(TestPrintPackageLoaded))
TestPrintPackageLoaded();

--sum: 
--	(1)'1'ֻ��ӡ��һ�Σ�����require��ʵֻ�Ǽ�����һ��random.lua�ļ�
--	(2)����Ϊrequire�ļ��ط�ʽ�ǰ��Ѿ����ص����ݷŵ���package.loaded���ˣ����Ժ���Ͳ������
-- local mRandom_1 = require("random")


-- print(getfenv(2))