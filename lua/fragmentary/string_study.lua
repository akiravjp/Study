--2013-09-18
--[[
a = "hello, world!hello, li!"
p, q = print(string.find(a, "hello"))
while(p) do
	print(p, q)
	p, q = print(string.find(a, "hello"))
end
]]
--2
--[[
b = "test(char)"
print(b)
print(string.find(b, "%(.*%)"))
c = string.reverse(b)
print(c)
p1, p2 = string.find(c, "%).*%(")
d= string.sub(c, p2+1)
print(d)
print(string.reverse(d))
]]
--[[
szFamilyName = "sdf(Title)"
nPos1 = string.find(szFamilyName, "%(")
szFamilyName1 = string.sub(szFamilyName, 1, nPos1-1)
print(11, szFamilyName1)
]]

----------------------------------------
--20.3 captures
--[[
pair = "name = Anna"
local n1, n2, key, value = string.find(pair, "(%a+)%s*=%s*(%a+)")
print(n1, n2, key, value)
--
local szName = "a,b,c"
--����

function split(str,splitor)
	if(splitor==nil) then
		splitor=','
	end
	local strArray={}
	local strStart=1
	local splitorLen = string.len(splitor)
	local index=string.find(str,splitor,strStart,true)
	if(index==nil) then
		strArray[1]=str
		return strArray
	end
	local i=1
	while index do
		strArray[i]=string.sub(str,strStart,index-1)
		i=i+1
		strStart=index+splitorLen
		index = string.find(str,splitor,strStart,true)
	end
	strArray[i]=string.sub(str,strStart,string.len(str))
	return strArray
end

local tbData = split(szName)
for k, v in pairs(tbData) do
	print(k, v)
end
]]

------------------------------
local szTest = "A"
--print(string.len(szTest))
--kmp
function kmp_next(szMode)
	local tbNext = {}
	szMode = tostring(szMode)
	tbNext[1] = 0;
	for j=2, string.len(szMode) do
		local i = tbNext[j-1];
		while szMode[j] ~= szMode[i+1] and i >= 1 do
			i = tbNext[i]
		end
		if szMode[j] == szMode[i+1] then
			tbNext[j] = i + 1
		else
			tbNext[j] = 0;
		end
	end
	return tbNext
end

function get_next(szMode)
	--print(szMode)
	local tbNext = {}
	szMode = tostring(szMode)
	local len = string.len(szMode)
	tbNext[1] = 0;
	local i = 1;
	local k = 0;
	--print("len", len)
	while i < len do
		--print("k, i", k, i, szMode[i], szMode[k])
		local szI = string.sub(szMode, i, i)
		local szK = string.sub(szMode, k, k)
		--print("szI, szK", szI, szK)
		
		if k == 0 or szI == szK then
			k = k + 1;
			i = i + 1;
			local szI = string.sub(szMode, i, i)
			local szK = string.sub(szMode, k, k)
		
			if szI ~= szK then
				tbNext[i] = k
			else
				tbNext[i] = tbNext[k];
			end
		else			
			k = tbNext[k];
		end
	end
	return tbNext
end

function kmp1(szDst, szMode)
	local tbNext = get_next(szMode)
	if #tbNext <= 0 then return; end
	
	local p = 1
	local s = 1
	while p <= string.len(szMode) and s <= string.len(szDst) do
		local cDst = string.sub(szDst, p, p)
		local cMod = string.sub(szMode, s, s)
		if cDst == cMod then
			p = p + 1;
			s = s + 1;
		else
			if p == 1 then
				s = s + 1;
			else
				p = tbNext[p-1] + 1;
			end
		end
	end
	
	if p < string.len(szMode) then
		return -1;
	end
	return s - string.len(szMode)
end

function kmp(szDst, szMode)
	local tbNext = get_next(szMode)
	if #tbNext <= 0 then return; end
	
	local p = 1
	local s = 1
	while p <= string.len(szMode) and s <= string.len(szDst) do
		local cDst = string.sub(szDst, p, p)
		local cMod = string.sub(szMode, s, s)
		if cDst == cMod then
			p = p + 1;
			s = s + 1;
		else
			p = tbNext[p];
		end
	end
	
	if p == string.len(szMode) then
		return s - p;
	end
	return -1;
end

function kmp_ex(szDst, szMode)
	--print(szDst, szMode)

	local lenDst = string.len(szDst)
	local lenMod = string.len(szMode)

	--if lenDst ~= lenMod then return -2; end
	local tbNext = get_next(szMode)

	if #tbNext <= 0 then return -2; end
	
	local p = 1
	local s = 1
	while p <= string.len(szMode) and s <= string.len(szDst) do
		local cDst = string.sub(szDst, p, p)
		local cMod = string.sub(szMode, s, s)
		--print("cDst, cMod", cDst, cMod)
		if cDst == cMod then
			p = p + 1;
			s = s + 1;
		else
			--if tbNext[p] == 0 then
				--return tbNext[p] + 1
			--else
				return s, tbNext[p];
			--end
		end
	end
	--print(p, s)
	--if p == string.len(szMode) then
	--	return -1;
	--end
	return -1;
end

--local tbNext = get_next("abcabaa")
--local tbNext = get_next("abcaabbabcabaacbacba")
--local tbNext = get_next("aaaadd")
--for k, v in pairs(tbNext) do
--	print(k, v)
--end
--local szMode = "aab"
--local szDst = "aaa"
--local pos = kmp_ex(szDst, "aab")
--print("pos: ", pos)

function random_seq(len)
	local szSeq = ""
	for i=1, len do
		local r = math.random(2)
		szSeq = szSeq .. tostring(r);
	end
	return szSeq
end

function test_kmp()
	for i=1, 5 do
		local szDst = random_seq(2)
		local szMod = random_seq(3)
		print(szDst, szMod)
		local posDst, posMod = kmp_ex(szDst, szMod)
		print("pos: ", posDst, posMod)
	end
end

--[[
121	221
pos: 	0
122	212
pos: 	0
221	111
pos: 	0
112	111
pos: 	2
112	222
pos: 	0
]]
--print(kmp_ex("12", "112"))
--test_kmp();

--[[
12	122
pos: 	-1	nil
11	222
pos: 	1	0
12	221
pos: 	1	0
11	111
pos: 	-1	nil
21	111
pos: 	1	0
]]
--print(kmp_ex("222", "12"))

function CmpKill2Mode(szKill, szMode)
	--if string.len(szKill) ~= string.len(szMode) then return -1; end
	--if szKill == szMode then
	--	return 0;
	--end
	local nPos = string.find(szKill, szMode)
	if nPos then 
		return 0, nPos + string.len(szMode);	--����ֻҪ�ڶ�������
	end
	local szTemp = szKill
	local nLen = string.len(szTemp)
	while nLen > 1 do
		szTemp = string.sub(szTemp, 2, nLen)
		local nPos = string.find(szMode, szTemp)
		--print(szTemp, nPos)
		if nPos and nPos == 1 then
			return nLen-1, nPos;
		end
		nLen = string.len(szTemp)
	end
	
	if nLen == 1 then
		local szMode_1 = string.sub(szMode, 1, 1)
		--print(szKill, szMode_1)
		if szKill == szMode_1 then
			return 1, 1
		end
	end
	return -1;
end
for i = 1, 10 do
	local sz1 = random_seq(6)
	local sz2 = random_seq(5)
	local nRet, nPos = CmpKill2Mode(sz1, sz2)
	if nRet >= 0 then
		--print(sz1, sz2, nRet, nPos)
	end
end

local nRet, nPos = CmpKill2Mode("1", "112")
-- print(nRet, nPos)
--local szTest = string.sub("221", nPos, string.len("221"))
--print(szTest, string.len(szTest))

-------------------------
--����ʲô�÷���
function CheckLua()
	local s = "a string with \r and \n and \r\n and \n\r"
	print(10, s)
	local c = string.format("return %q", s)
	local z = assert(loadstring(c))()
	print(11, z)
	print(12, a == s)
	assert(assert(loadstring(c))() == s)
end
-- print(111, CheckLua())


local tbTest = {1, 2, 3}
--tbTest[2], tbTest[3] = tbTest[3], tbTest[2]
for k, v in ipairs(tbTest) do
	--print (k, v)
end

function AllPerm(tbTest)
	--test
	--print("AllPerm start......", #tbTest)
	for k, v in ipairs(tbTest) do
		--print(v)
	end
	
	if #tbTest == 1 then
		print(tbTest[1], ",")
		return;
	end
	
	--copy
	local tbData = {}
	for _, v in ipairs(tbTest) do
		table.insert(tbData, v)
	end
	
	local tbPerm = {}
	for k, v in ipairs(tbTest) do
		--change
		tbData[k], tbData[#tbData] = tbData[#tbData], tbData[k]
		print(tbData[#tbData], ",")
		
		local n = table.remove(tbData)
		AllPerm(tbData)
		print(".....", n)
		
		--copy back
		tbData = {}
		for _, v in ipairs(tbTest) do
			table.insert(tbData, v)
		end
	end
	
	--copy back
	--for _, v in ipairs(tbTest) do
	--	table.insert(tbData, v)
	--end
end

--AllPerm(tbTest)

--2015/01/29 string.len("")
-- print(string.len(""))

--2015/08/25 ����
local pair = "name = Anna"
local key, value = string.match(pair, "(%a+)%s*=%s*(%a+)")
print(key, value)
-- local pair1 = "��xxx�� jiu��������e"
-- local s1, s2 = string.match(pair1, "��(.*)��%s*(.*)");
-- print(pair1, s1, s2);
-- local s3, s4 = string.find(pair1, "��%s")
-- print(s3, s4);

-- print(os.date("%X", os.time()))
-- print(os.date("%p", os.time()))
-- print(os.date("%H:%M", os.time()))

-- add a postfix 2017/12/23
local szTest = "PaperSprite'/Game/UI/Icon/Skill/GS/Frames/gs_icon0000.gs_icon0000'";
local szPath, szEnd = string.match(szTest, "PaperSprite'(.+)%.(.+)'");
print("szPath = ", szPath, szEnd)
print("new = ", string.format("PaperSprite'%s_D.%s_D'", szPath, szEnd))

-- 2015/08/26 ����������
function addMessageTipsEx(...)
	local massage = string.format("%s:%d", ...)
	print(massage);
end

-- addMessageTipsEx("test", 6);

-- 2015/12/23 �Ƚ�ʱ��
function compare()
	local nMax = 1000000;
	local t1 = os.clock();
	for i = 1, nMax do
		if "asdggasddg4" == "aakjpllsgc" then
		end
	end
	local t2 = os.clock()
	print(111, t2-t1);
	
	local n1 = math.random(100000);
	local n2 = math.random(100000);
	local t3 = os.clock();
	for i = 1, nMax do
		if n1 == n2 then
		end
	end
	local t4 = os.clock()
	print(222, t4-t3);
end

-- compare();

------------------------------------------------------------
-- 2016/10/10 �ж���û��ǰ16���ַ���ͬ��ħ�����Դ�
local tbMagicString = {
	"common_probability",											-- ͳһ�ɹ�����
	"back_attack_damage_add_percent",								-- �����˺������ӳ�
	"skilling_attack_damage_add_percent",							-- �Ƽ��˺������ӳ�
	"back_attack_injury_add_percent",								-- ��������ֵ�����ӳ�
	"skilling_attack_injury_add_percent",							-- �Ƽ�����ֵ�����ӳ�
	"damage_destroy_zhen",											-- ����
	"damage_direct_death",											-- ֱ������
	"damage_direct_death_by_npc_type",								-- ����Npc����ֱ������
	"damage_pn_attack_add",											-- ����״̬�����ӳ�	
	"damage_attack_enemy_def_add",									-- ���˷��������Թ������ӳ�(ר����Ը߷��ĵ���)
	"damage_ignore_rebound_per",									-- �˺�������������
	"damage_cancle_knockdown",										-- ȡ�����أ����ʣ�
	"damage_beat_partner_value",									-- ���ֵ
	"damage_knockdown",												-- ����������+������������
	"damage_knockback",												-- ���ˣ�ֻ�м��ʣ�	
	"damage_beat_move",												-- ����λ�Ʊ���
	"damage_beat_ctrl",												-- ��������λ�Ʊ���
	"damage_add_defense_percent",									-- �Է���״̬NPC�����˺��ٷֱ�
	"damage_add_breakdefense_percent",								-- ���Ʒ�״̬NPC�����˺��ٷֱ�
	"damage_add_defense_point",										-- �Է���״̬NPC�����˺�����
	"damage_add_breakdefense_point",								-- ���Ʒ�״̬NPC�����˺�����
	"critical_add_defense_per10k",									-- ��������Ŀ�����ӱ������ʣ���ֱ�
	"critical_add_breakdefense_per10k",								-- �����Ʒ�Ŀ�����ӱ������ʣ���ֱ�
	"critical_add_damage_defense",									-- ��������Ŀ�����ӱ����˺����ٷֱ�
	"critical_add_damage_breakdefense",								-- �����Ʒ�Ŀ�����ӱ����˺����ٷֱ�
	"critical_damage_odds_add_percent",								-- ����Ŀ�걩���˺����ʰٷֱ�����
	"damage_add_by_missle_fly_time",								-- �����ӵ�����ʱ�������˺�
	"damage_yin_life",												-- �˺��������Ե�λ����
	"damage_life",													-- �˺�������
	"damage_mana",													-- �˺�������
	"damage_stamina",												-- �˺�������
	"damage_life2",													-- 
	"damage_absorb_life",											-- ��ȡ����
	"damage_absorb_mana",											-- ��ȡ����
	"damage_absorb_stamina",										-- ��ȡ����
	"damage_weapon_perdure",										-- �˺������־ö�
	"damage_armor_perdure",											-- �˺����߳־ö�
	"damage_cause_i_wound_level",									-- �����˵ȼ�
	"damage_cause_o_wound_level",									-- �����˵ȼ�
	"damage_thieve_money",											-- ͵ȡ��Ǯ����
	"damage_thieve_skill",											-- ͵ȡ״̬
	"damage_thieve_item",											-- ͵ȡ��Ʒ
	"damage_dispell_type",											-- ״̬�������
	"damage_dispell_num",											-- ״̬�����Ŀ
	"damage_self_perdure_p",										-- �����־ö����
	"damage_reserved",												-- ����ʹ������(��������ݲ�ͬ���ܶ���)
	"damage_add_enmity_p",											-- ��޶����ӱ���
	"damage_draw_near",												-- ��Ŀ��������ǰ
	"damage_interrupt_rate_add",									-- ��߹�����ϵ����书����
	"damage_retrusive_rate_add",									-- ��߹���ʹ���˺�������
	"damage_retrusive_time",										-- ������ɺ���ʱ�� ����֡Ϊ��λ
	"damage_retrusive_time_limit",									-- ����ʱ�����ޣ���֡Ϊ��λ
	"damage_life_monster",											-- ���Npc�������˺�
	"damage_change_position",										-- ��Ŀ�껻λ��
	"damage_zhen",													-- ������״̬
}

function fnFindPre16( tbStrings )
	local tbStrings = tbStrings or {};
	local tbHashPre16 = {};
	for _, str in paris(tbStrings) do
		-- ��ȡ�ַ���ǰ16���ַ�
		local strTmp = string.sub(str, 1, 16);
	end
end

--[[sum:
* �õ����ַ���ָ�룬16���ַ���ָ�룬��������˵�ַ�������Ϊ16��
* ���룺char* ppString[nStringCount] = {0};
]]

------------------------------------------------------------
-- 2017-09-02 13:44:51
-- stackoverflow

a = "stackoverflow.com/questions/ask"

-- print(string.match(a,"(.*/)"))   -- stackoverflow.com/questions/
-- print(string.match(a,"((.*/).*)")) -- stackoverflow.com/questions/


------------------------------------------------------------
 -- 2017-09-13 12:12:25
 -- stackoverflow match
 local function splitString(text)
    pattern = "<(%a+)>%s*([^>]+)"
    i,j = string.match(text, pattern)
    return i,j
end

-- print(splitString("<c> block"))           -- c  block
-- print(splitString("<category>material"))  -- category   material
-- print(splitString("decorative"))          -- nil    nil

------------------------------------------------------------
-- string array
local szString = "abcdefghijklmnopqrstuvwxyz";
-- print(szString[2])

------------------------------------------------------------
 -- 2020-04-10 11:51:25
 -- stackoverflow match
function testMatch()
	-- https://stackoverflow.com/questions/61130773/how-to-get-string-multi-word-between-characters
	local str = "Reason = Failed to connect ( Nickname: Mc Gee ), Banned by: Andrew"
	print(str)
	-- local key, value = string.match(pair, "[%a%s]+(*(%a+)%s*=%s*(%a+)")
	local szKey, szName = string.match(str, "Reason = [%a%s]+%([%a%s]+:%s+(.*)%s+%).*");
	print(szName)
	print(string.match(str, "Reason = [%a%s]+%([%a%s]+:%s+(.*)%s+%).*"))
	-- print(string.match(str, "(.*)"))
	-- print(str:match("%b()"):gsub("[()]","")) -- prints ` Nickname: Mc Gee `
	-- print(str:match("%b()")) -- 
end
-- testMatch();


------------------------------------------------------------
-- data\source\player\f1\����\mdl\f1.mdl
function fnGetBodyType(szModel)
	local szModel = szModel or "data\\source\\player\\f1\\����\\mdl\\f1.mdl";
	local szType = string.match(szModel, ".*\\(%a+%d+)_-[%a%d]-.mdl");
	print(111, szType);
end
-- fnGetBodyType();
-- fnGetBodyType("data\\source\\player\\m1\\����\\mdl\\m1_player.mdl");


print(string.format("xxx%d %%, %.1f", 1, 0.1));


-------------------------------------------------------------------------
string.split = function(str, sep)
    local rt     = {};
    local bEmpty = false;
    if type(str) ~= "string" or type(sep) ~= "string" then
        return rt, bEmpty;
    end
    string.gsub(str, '[^' .. sep .. ']+', function(w)
        table.insert(rt, w)
    end);
    bEmpty = (rt and #rt == 1 and rt[1] == "\0");
    return rt, bEmpty;
end
-- local tbSplit = string.split("aabbccbc", "bb");
local tbSplit = string.split(" ,123", ",");
for k, v in ipairs(tbSplit) do
	print(k, v, type(v))
end

-------------------------------------------------------------------------
-- ������� @2021/05/07
-- ��֧�ֲ���
string.rfind = function(str, pattern, pos)
	local pos = pos or -1;
	local rstr = string.reverse(str);
	local rpattern = string.reverse(pattern);
	local rpos = -pos;
	print(1, rstr);
	print(2, rpattern);
	print(3, rpos);
	local s, e = string.find(rstr, rpattern, rpos)
	print("rfind: ", s, e)
	local l = string.len(str);
	return l - e + 1, l - s + 1;
end

function test_rfind()
	a = "hello, world!hello, li!hello hi"
	p, q = string.find(a, "hello")
	print("p, q = ", p, q, t)
	local s, e = string.rfind(a, "hello");
	print(s, e)

	-- b = "test(char)"
	-- print(b)
	-- print(string.find(b, "%(.*%)"))
	-- string.rfind(b, "%(.*%)");

	local szPath = "script/gameplay/building/anchor/building_anchor.lua";
	-- local nPos = string.rfind(szPath, '%.');
	-- print(nPos)
	-- local szPath1 = string.sub(szPath, 1, nPos);
	-- szPath1 = szPath1 .. ".Json"
	-- print(szPath1)

	--
	-- ��math�Һ�׺ : https://stackoverflow.com/questions/17386792/how-to-implement-string-rfind-in-lua
	local szPath2 = string.match(szPath, ".*%.")
	print(szPath2)

	szPath = "data/source/maps/ƽҰ�º�/ƽҰ�º�.jsonmap"
	szPath = "data\\source/maps/ƽҰ�º�\\ƽҰ�º�.jsonmap"
	local name = string.match(szPath, ".+[/\\](.+)%..+")
	print(name)
end
-- test_rfind();

function test_lower(  )
	local szPath = "data\\source\\M_buildingFinal\\��������\\City_C_LV01_�����01_1x1.Scenenode"
	szPath = string.lower(szPath);
	print(szPath)

	-- local szNil = stirng.lower(nil);
end
-- test_lower();

function test_replace()
	-- ��⣺
	-- * �����%n��n��ָ��()�ĵڼ����������������������Ȼ(%w+)���������Σ��ֱ���hello��world������max(n) = 1����������%2��ʱ��ᱨ��
	-- * ����һ�㣬���Կ�����%n�õ��ǵ�ǰ�����ֵ����Ϊһ�β�����ܻ������������������hello��world
	local x, y = string.gsub("hello world", "(%w+)", "%1 %1");
	x, y = string.gsub("hello world", "%w+", "%1 %1");
	print(x, y)
	-- ��⣺The sequence %0 stands for the whole match. 
	-- * %0���ȷ���һ�������ԭ�ģ����Ϊ%0���Դ�������һ��%n������Ҫ�����ĸ��أ���Ҫ�ټ�һ������������
	-- * �������Ϊ1����"%0 %0"�ͱ�ʾ"%1 %1"�����Ǻ����治iһ�����ǣ������1��������һ����˼��ֻ�滻�ڼ��β���
	-- * �������Ϊ%n, n=[0, 9]�Ĵ���������
	--[[
	nCurIndex = 1
	string.gsub(s, pattern, %n..., num)
	��ÿһ�β���ִ�����º���
	hash[nMatchIndex1-9] = match string
	function(v) 
		if nCurIndex <= num then
			local szNew = �����е�%n����hash[nMatchIndex]������n = 0������hash[nCurIndex]
			-- replace pattern with szNew
		end
	end
	]]
	x = string.gsub("hello world", "%w+", "%0 %0", 1)	-- hello hello world
	x = string.gsub("hello world", "%w+", "%0 %0 %0", 1)	-- hello hello hello world
	x = string.gsub("hello world", "%w+", "%0 %0", 2)	-- hello hello world world
	x = string.gsub("hello world", "%w+", "%0 %0 %0", 2)	-- hello hello hello world world world
	x = string.gsub("hello world pnj", "%w+", "%0 %0", 3)	-- hello hello world
	print(x)

	x = string.gsub("hello world", "%w+", "a", 1)
	print(x)
	x = string.gsub("hello world", "%w+", function( v )
		print(222, v)
	end)

	-- x = string.gsub("hello world", "%w+", function(v)
	-- 	print(111, v); 
	-- end)

	local szPath = "Season_ƽҰ��Į.anchor";
	local szPath = "aaa_bbb.txt";
	local szMatchName = string.match(szPath, ".+_(.+)%..+");
	print("szMatchName = ", szMatchName)
	local szNewName = string.gsub( szPath, "(_.+)%.", "_" .. 666 .. ".")
	print("szNewName = ", szNewName)
	local szNumber = string.match(szNewName, ".+_(.+)%..+");
	print(szNumber, tonumber(szNumber))
	szNumber = string.match("aaa_bbs6.anchor", ".+_(.+)%..+");
	print(szNumber, tonumber(szNumber))
end
test_replace();