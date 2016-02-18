-------------------------------------------------------
-- file:		knap_sack.lua
-- author:		page
-- time:		2015/12/18
-- desc:		0-1�����㷨
-- ref:
--[[
	* http://www.cnblogs.com/Anker/archive/2013/05/04/3059070.html	--> �㷨����
	* http://blog.csdn.net/livelylittlefish/article/details/2186206 --> ��ⲿ��
	* http://www.importnew.com/13072.html							--> ͼ�λ�����
]]
-------------------------------------------------------

--0-1����

function bag(n, w, tbValue, tbWeight)
	local tbRet = {};
	-- ��ʼ��������
	for row = 0, n do
		tbRet[row] = {};
	end
	
	-- ��ʼ����һ��
	for col = 0, w do
		tbRet[0][col] = 0;
	end
	
	-- ��ʼ����
	for row = 1, n do
		tbRet[row][0] = 0;
		for col = 1, w do
			local wT = tbWeight[row];
			if wT <= col then
				local nNew = tbValue[row] + tbRet[row-1][col-wT];
				tbRet[row][col] = math.max(nNew, tbRet[row-1][col]);
			else
				tbRet[row][col] = tbRet[row-1][col];
			end
		end
	end
	
	-- ��ӡ������
	for row = 0, n do
		local szRet = "";
		for col = 0, w do
			local szTemp = string.format("%5d", tbRet[row][col]);
			szRet = szRet .. szTemp .. ",";
		end
		-- print(szRet);
	end
	print("the ret is: ", tbRet[n][w]);
	
	-- ���
	local tbSelect = {};
	local col = w;
	for row = n, 1, -1 do
		if tbRet[row][col] > tbRet[row-1][col] then
			tbSelect[row] = true;
			col = col - tbWeight[row];
		else
			tbSelect[row] = false;
		end
	end
	
	-- ��ӡ�����
	for row, ret in pairs(tbSelect) do
		if ret then
			print("the item " .. row .. "(" .. tbValue[row] .. ")" .. "is selected!");
		end
	end
end

local tbValue = {10, 40, 30, 50};
local tbWeight = {5, 4, 6, 3};
local n = 4;
local w = 10;

bag(n, w, tbValue, tbWeight);