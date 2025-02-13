require "string/string"
require "tool"
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

function find_test()
	local szContent = "老友，你这沿街叫卖的手法可真是巧妙啊。";
	local szContent = "大娘，不用担心。虽然年纪不小了，但我还有点力气，还能吸引些路人购买呢。";
	-- local szContent = "这位兄弟, 你看这老头沿街叫卖的声音挺大，似乎吸引了不少人购买。";
	local n, a, b = string.find(szContent, "[,，]");
	local szTitle = string.sub(szContent, 1, n-1);
	local szNewContent = string.sub(szContent, n);
	print(n, a, b, szTitle, szNewContent);
end
find_test();
----------------------------------------
--20.3 captures
--[[
pair = "name = Anna"
local n1, n2, key, value = string.find(pair, "(%a+)%s*=%s*(%a+)")
print(n1, n2, key, value)
--
local szName = "a,b,c"
--迭代

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
		return 0, nPos + string.len(szMode);	--这里只要第二个参数
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

-- local nRet, nPos = CmpKill2Mode("1", "112")
-- print(nRet, nPos)
--local szTest = string.sub("221", nPos, string.len("221"))
--print(szTest, string.len(szTest))

-------------------------
--这是什么用法？
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

--2015/08/25 捕获
local pair = "name = Anna"
local key, value = string.match(pair, "(%a+)%s*=%s*(%a+)")
-- print(key, value)
-- local pair1 = "【xxx】 jiu是这样的e"
-- local s1, s2 = string.match(pair1, "【(.*)】%s*(.*)");
-- print(pair1, s1, s2);
-- local s3, s4 = string.find(pair1, "【%s")
-- print(s3, s4);

-- print(os.date("%X", os.time()))
-- print(os.date("%p", os.time()))
-- print(os.date("%H:%M", os.time()))

-- add a postfix 2017/12/23
local szTest = "PaperSprite'/Game/UI/Icon/Skill/GS/Frames/gs_icon0000.gs_icon0000'";
local szPath, szEnd = string.match(szTest, "PaperSprite'(.+)%.(.+)'");
-- print("szPath = ", szPath, szEnd)
-- print("new = ", string.format("PaperSprite'%s_D.%s_D'", szPath, szEnd))

-- 2015/08/26 不定长参数
function addMessageTipsEx(...)
	local massage = string.format("%s:%d", ...)
	print(massage);
end

function addMessageTipsEx1(...)
	
end

-- addMessageTipsEx("test", 6);
-- addMessageTipsEx("test", 6);

-- 2015/12/23 比较时间
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
-- 2016/10/10 判断有没有前16个字符相同的魔法属性串
local tbMagicString = {
	"common_probability",											-- 统一成功几率
	"back_attack_damage_add_percent",								-- 背击伤害比例加成
	"skilling_attack_damage_add_percent",							-- 破技伤害比例加成
	"back_attack_injury_add_percent",								-- 背击气绝值比例加成
	"skilling_attack_injury_add_percent",							-- 破技气绝值比例加成
	"damage_destroy_zhen",											-- 破阵
	"damage_direct_death",											-- 直接致死
	"damage_direct_death_by_npc_type",								-- 根据Npc类型直接致死
	"damage_pn_attack_add",											-- 两仪状态攻击加成	
	"damage_attack_enemy_def_add",									-- 敌人防御比例对攻击力加成(专门针对高防的敌人)
	"damage_ignore_rebound_per",									-- 伤害反弹削减比例
	"damage_cancle_knockdown",										-- 取消倒地（几率）
	"damage_beat_partner_value",									-- 打击值
	"damage_knockdown",												-- 击倒（几率+后退坐标数）
	"damage_knockback",												-- 击退（只有几率）	
	"damage_beat_move",												-- 被击位移表现
	"damage_beat_ctrl",												-- 被击控制位移表现
	"damage_add_defense_percent",									-- 对防御状态NPC增加伤害百分比
	"damage_add_breakdefense_percent",								-- 对破防状态NPC增加伤害百分比
	"damage_add_defense_point",										-- 对防御状态NPC增加伤害点数
	"damage_add_breakdefense_point",								-- 对破防状态NPC增加伤害点数
	"critical_add_defense_per10k",									-- 攻击防御目标增加暴击概率，万分比
	"critical_add_breakdefense_per10k",								-- 攻击破防目标增加暴击概率，万分比
	"critical_add_damage_defense",									-- 攻击防御目标增加暴击伤害，百分比
	"critical_add_damage_breakdefense",								-- 攻击破防目标增加暴击伤害，百分比
	"critical_damage_odds_add_percent",								-- 攻击目标暴击伤害概率百分比增加
	"damage_add_by_missle_fly_time",								-- 根据子弹飞行时间增加伤害
	"damage_yin_life",												-- 伤害减阴属性单位生命
	"damage_life",													-- 伤害减生命
	"damage_mana",													-- 伤害减内力
	"damage_stamina",												-- 伤害减体力
	"damage_life2",													-- 
	"damage_absorb_life",											-- 吸取生命
	"damage_absorb_mana",											-- 吸取内力
	"damage_absorb_stamina",										-- 吸取体力
	"damage_weapon_perdure",										-- 伤害武器持久度
	"damage_armor_perdure",											-- 伤害防具持久度
	"damage_cause_i_wound_level",									-- 致内伤等级
	"damage_cause_o_wound_level",									-- 致外伤等级
	"damage_thieve_money",											-- 偷取金钱数量
	"damage_thieve_skill",											-- 偷取状态
	"damage_thieve_item",											-- 偷取物品
	"damage_dispell_type",											-- 状态清除类型
	"damage_dispell_num",											-- 状态清除数目
	"damage_self_perdure_p",										-- 武器持久度损耗
	"damage_reserved",												-- 保留使用属性(其意义根据不同技能而定)
	"damage_add_enmity_p",											-- 仇恨度增加比例
	"damage_draw_near",												-- 把目标拉到身前
	"damage_interrupt_rate_add",									-- 提高攻击打断敌人武功概率
	"damage_retrusive_rate_add",									-- 提高攻击使敌人后仰概率
	"damage_retrusive_time",										-- 技能造成后仰时间 ，以帧为单位
	"damage_retrusive_time_limit",									-- 后仰时间下限，以帧为单位
	"damage_life_monster",											-- 针对Npc的生命伤害
	"damage_change_position",										-- 和目标换位置
	"damage_zhen",													-- 设置阵法状态
}

function fnFindPre16( tbStrings )
	local tbStrings = tbStrings or {};
	local tbHashPre16 = {};
	for _, str in paris(tbStrings) do
		-- 截取字符串前16个字符
		local strTmp = string.sub(str, 1, 16);
	end
end

--[[sum:
* 用的是字符串指针，16个字符串指针，而并不是说字符串长度为16。
* 代码：char* ppString[nStringCount] = {0};
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
	local tbContentTest = {
		-- "笑着回答：年级大了",
		-- "就是年级大了",
		-- ":你好啊",
		-- "ABC:你说哈",
		-- "我喜欢讲故事传说，这是我最大的爱好。我还喜欢观察和思考，总能从中获得乐趣和启示。",
		-- "，",
		"宋德祥：嗯，我认识李小花。她是村里年轻有为的女孩子，勤劳善良，受到大家的喜爱。她经营着一家小饭馆，做的菜非常美味。如果你想品尝一下当地的特色菜肴，可以去找她。",
		[[
			宋德祥听到提到钓鱼的问题，他笑了笑，说道："钓鱼啊，那可是一门好技术！我年轻时可是爱钓鱼的，每次都能钓到很多鱼呢。你有什么关于钓鱼的问题吗？我很乐意分享我的经验。"
		]],
	}
	
	-- \uff0c 为中文名冒号
	for k, v in ipairs(tbContentTest) do
		local szContent = string.match(v, ".*:(.*)");
		local szContent1 = string.match(v, ".*：(.*)");
		-- local nPos = string.find(v, "：");
		-- local nPos1 = string.find(v, ":");
		-- print(nPos, nPos1)
		-- szContent = (nPos or nPos1) and szContent or szContent1 or v;
		print("szContent = ", szContent, szContent1)

		-- local szContent = string.match(v, ".*[:：](.*)");
		-- print("match = ", szContent)
	end

	local szContent = [[
		好感度变化得分：1
		信息密度得分：1
		恰当的回复：钓鱼可能对你来说无聊，但对我来说却是一种放松身心的方式，你可以尝试一下。
	]]
	szContent = string.trim(szContent);
	local tbRet = string.split(szContent, "\n");
	print(tbRet, #tbRet)
	for k, v in ipairs(tbRet) do
		local szReslt = string.match(v, ".*：(.*)");
		print(k, v, szReslt);
	end
end
-- testMatch();

function GetFileName(szFullPath)
	local szFullPath = szFullPath or "$(ProgramFiles)\\Windows Kits\\10\\Include\\10.0.18362.0\\um\\winresrc.h";
	-- local szFileName = string.match(szFullPath, ".+/([^/]*%.%w+)$"); -- *linux
	local szFileName = string.match(szFullPath, ".*\\([^\\]*%.%w+)$"); -- windows
	print(szFileName);
end
-- GetFileName();
------------------------------------------------------------
-- data\source\player\f1\部件\mdl\f1.mdl
function fnGetBodyType(szModel)
	local szModel = szModel or "data\\source\\player\\f1\\部件\\mdl\\f1.mdl";
	local szType = string.match(szModel, ".*\\(%a+%d+)_-[%a%d]-.mdl");
	print(111, szType);
end
-- fnGetBodyType();
-- fnGetBodyType("data\\source\\player\\m1\\部件\\mdl\\m1_player.mdl");


-- print(string.format("xxx%d %%, %.1f", 1, 0.1));


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
-- for k, v in ipairs(tbSplit) do
-- 	print(k, v, type(v))
-- end

-------------------------------------------------------------------------
-- 反向查找 @2021/05/07
-- 不支持捕获
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
	-- 用math找后缀 : https://stackoverflow.com/questions/17386792/how-to-implement-string-rfind-in-lua
	local szPath2 = string.match(szPath, ".*%.")
	print(szPath2)

	szPath = "data/source/maps/平野孤鸿/平野孤鸿.jsonmap"
	szPath = "data\\source/maps/平野孤鸿\\平野孤鸿.jsonmap"
	local name = string.match(szPath, ".+[/\\](.+)%..+")
	print(name)
end
-- test_rfind();

function test_lower(  )
	local szPath = "data\\source\\M_buildingFinal\\基础建筑\\City_C_LV01_乱葬岗01_1x1.Scenenode"
	szPath = string.lower(szPath);
	print(szPath)

	-- local szNil = stirng.lower(nil);
end
-- test_lower();

function test_replace()
	-- 理解：
	-- * 这里的%n的n是指的()的第几个，比如下面这个里面虽然(%w+)捕获了两次，分别是hello和world，但是max(n) = 1，所以我用%2的时候会报错
	-- * 另外一点，可以看出来%n用的是当前捕获的值，因为一次捕获可能会满足多个，比如这里的hello和world
	local x, y = string.gsub("hello world", "(%w+)", "%1 %1");
	x, y = string.gsub("hello world", "%w+", "%1 %1");
	print(x, y)
	-- 理解：The sequence %0 stands for the whole match. 
	-- * %0：先翻译一下上面的原文，理解为%0可以代表任意一个%n，但是要代表哪个呢？需要再加一个参数来决定
	-- * 比如参数为1，那"%0 %0"就表示"%1 %1"，但是和上面不i一样的是，这里的1还有另外一个意思是只替换第几次捕获
	-- * 可以理解为%n, n=[0, 9]的代码是这样
	--[[
	nCurIndex = 1
	string.gsub(s, pattern, %n..., num)
	对每一次捕获执行以下函数
	hash[nMatchIndex1-9] = match string
	function(v) 
		if nCurIndex <= num then
			local szNew = 把所有的%n换成hash[nMatchIndex]，对于n = 0，换成hash[nCurIndex]
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

	local szPath = "Season_平野荒漠.anchor";
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
-- test_replace();

------------------------------------------------------------------------------------------------------
--- 正则表达式查找
local tbEncoding = {
	"2.0.0.0.0",
	"2.0.0.0.[12]",
	"2.0.0.[12]0[12]",
	"2.0.[12].0.[12]",
	"2.0.[12]0[12]0[12]",
	"20[12]0[12]0[12]0[12]",
	"2.0.0.[12][12][12]",
	"2.0.[12][12][12][12][12]",
	"2[12][12][12][12][12][12][12][12]",
	"2.0.[12]0[12][12][12]",
	"2.0.[12][12][12]0[12]",
	"20[12]0[12]0[12][12][12]",
	"20[12][12][12]0[12][12][12]",
	"2[12][12][12][12]0[12][12][12]",
	"2[12][12][12][12]0[12]0[12]",
	"1.0.0.0.0",
	"1.0.0.0.1",
	"1.0.0.101",
	"1.0.1.0.1",
	"1.0.10101",
	"101010101",
	"1.0.0.1[12]1",
	"1.0.1[12]1[12]1",
	"1[12]1[12]1[12]1[12]1",
	"1.0.101[12]1",
	"1.0.1[12]101",
	"1010101[12]1",
	"101[12]101[12]1",
	"1[12]1[12]101[12]1",
	"1[12]1[12]10101",
	"1.0.0.0.2",
	"1.0.0.102",
	"1.0.0.201",
	"1.0.0.202",
	"1.0.1.0.2",
	"1.0.2.0.2",
	"1.0.10102",
	"1.0.20101",
	"1.0.10201",
	"1.0.20102",
	"1.0.1.202",
	"1.0.20201",
	"1.0.20202",
	"101010102",
	"101020102",
	"101010202",
	"102010202",
	"102020202",
	"1.0.0.1[12]2",
	"1.0.0.2[12]1",
	"1.0.0.2[12]2",
	"1.0.1[12].[12]2",
	"1.0.2[12]1[12]1",
	"1.0.1[12]2[12]1",
	"1.0.2[12]1[12]2",
	"1.0.1[12]2[12]2",
	"1.0.2[12]2[12]1",
	"1.0.2[12]2[12]2",
	"1.1.1.1.2",
	"1.1.2.1.2",
	"1.1.1.2.2",
	"1.1.2.2.2",
	"1.2.2.2.2",
	"1.0.101[12]2",
	"1.0.201[12]1",
	"1.0.102[12]1",
	"1.0.201[12]2",
	"1.0.102[12]2",
	"1.0.202[12]1",
	"1.0.202[12]2",
	"1.0.1[12]102",
	"1.0.2[12]101",
	"1.0.1[12]201",
	"1.0.2[12]102",
	"1.0.1[12]202",
	"1.0.2[12]201",
	"1.0.2[12]202",
}

function TestExpFind()
	-- local a1 = string.find("a1111", "a111.");
	-- print("a1 = ", a1)

	local szExp = "1.0.0.0.1";
	local a= string.find("100000001", szExp);
	-- print("a = ", a);

	local szExp = "1.0.0.1[12]1";
	a = string.find("100000121", szExp);
	print("a = ", a);
end

-- TestExpFind();
function CheckEncoding(tbEncoding, tbGridEncoding)
	math.randomseed(os.time());
	
	if not tbGridEncoding then
		tbGridEncoding = {};
		for i = 1, 9 do
			local nRandom = math.floor(math.random(1, 10000)) % 3;
			table.insert(tbGridEncoding, nRandom);
		end
	end

	local tbStartIndex = {2, 4, 6, 8};  -- {左上，右上，右下，左下}
    local nEndIndex = #tbGridEncoding;
    for k, v in pairs(tbStartIndex) do
        local szEncoding = tbGridEncoding[1] .. table.concat(tbGridEncoding, "", v, nEndIndex) .. table.concat(tbGridEncoding, "", 2, v-1);
        print("szEncoding = ", szEncoding);
		for k, v in pairs(tbEncoding) do
			local nPos = string.find(szEncoding, v);
			if nPos then
				print(v, nPos);
			end
		end
    end
end
-- CheckEncoding(tbEncoding);

------------------------------------------------------------------------------------------------------
local ShaderKeyword = {
    ["BRANCH"] = true,
    ["return"] = true,
    ["#elif"] = true,
    ["elif"] = true,
    ["else"] = true,
}

function _GetShaderFunctionName(szLine, nType)
    if not szLine then
        return;
    end
    
    local nStartPos, nEndPos = string.find(szLine, "//");
    if nStartPos == 1 and nEndPos == 2 then
        return;
    end
    
    local szPattern = "([%w_]+)%s+([%w_]+)%s*%(";
    if nType == 2 then
        szPattern = "([%w_]+)%s+([%w_]+)%s*=";
    end
    local szReturn, szName = string.match(szLine, szPattern);
    if ShaderKeyword[szReturn] then
        return;
    end
    if nType == 2 then
        local nStartPos, nEndPos = string.find(szLine, "=");
		local nNextPos = string.find(szLine, "%w", nStartPos + 1);
		if nNextPos then
			return;
		end
    end
    return szReturn, szName;
end

function TestGetFunctionName()
	------------------------------------------------------------------------------------------------------
	-- local szLine = "float4 PixelShaderMain(VertexOutput Input, uniform bool RenderSoftMask, PixelSystemInput SystemInput) : SV_Target0";
	-- local szLine = "				BRANCH if (EnableAlphaTest)";
	-- local szLine = "void PS_GBufferWriting(	//VertexOutput Input, ";
	-- local szLine = "#define SSSS_FOVY GetSSSFovY()"
	-- local szLine = "float unPremultLinearToSRGB(float c)";
	-- local szType, szName = string.match(szLine, "([%w_]+)%s+([%w_]+)%s*%(");
	-- local szType, szName = _GetShaderFunctionName(szLine);
	------------------------------------------------------------------------------------------------------
	-- local szLine = "GeometryShader MainVoxelizationWithGbufferGeometryShader = ";
	local szLine = "    int     g_nMatLayerMaskType = -1;   // Offset:   28, size:    4";
	print(111, string.len(szLine));
	szLine = (string.gsub(szLine, "^%s*(.-)%s*$", "%1"));
	print(222, string.len(szLine));
	local szType, szName = _GetShaderFunctionName(szLine, 2);
	------------------------------------------------------------------------------------------------------
	print("Name = ", szType, szName);
end
-- TestGetFunctionName();

------------------------------------------------------------------------------------------------------
function _GetShaderPathFromAssembly(szLine)
    if not szLine then
        return;
    end
    -- local szPattern = "%s*#line%s+([%d]+)%s+([%w\\/:%.-_]+)";
    local szPattern = "%s*#line%s+([%d]+)%s+\"([%w\\/:%.-_]+)\"";
    local szLine, szPath = string.match(szLine, szPattern);
	return szLine, szPath;
end

function TestGetShaderPath()
	-- local szLine = "        #line 196 h:\\svn\\BDCode\\sword3-products\\trunk\\client\\data\\material\\Shader_DX11_HD\\Voxelization.h5";
	-- local szLine = "#line 1995 \"h:\\svn\\BDCode\\sword3-products\\trunk\\client\\data\\material\\Shader_DX11_HD\\CommonParam.h\""
	local szLine = "#line 200";
	local szPattern = "%s*#line%s+([%d]+)%s*";
    local szLineNum = string.match(szLine, szPattern);
	print("Line = ", szLineNum)
	local nLine, szShaderPath = _GetShaderPathFromAssembly(szLine);
	print(nLine, szShaderPath);
end
-- TestGetShaderPath();

------------------------------------------------------------------------------------------------------
function TestGetAssemblyFunctionName()
	-- local szLine = "VertexShader MainVertexShader = KG3D_CompileVS(VertexShaderMain());";
	local szLine = "PixelShader SSSBlurShellShader = KG3D_CompilePS(SSSBlurShell(g_tSceneColor/*g_tSSS*/, g_tSceneDepth, g_tSceneColor/*g_tSSSSpecular*/, false));";
	-- local szLine = "PixelShader SoftMaskShader = KG3D_CompilePS(PixelShaderMain(true));";
	-- local szPattern = "[%w]+%s+([%w_]+)%s*=%s*KG3D_CompileVS%(([%w_]+%(%w*%))%)";	-- MainVertexShader        VertexShaderMain()
	-- local szPattern = "[%w]+%s+([%w_]+)%s*=%s*KG3D_CompileVS%(([%w_]+)(%(%w*%))%)";
	local szPattern = "[%w]+%s+([%w_]+)%s*=%s*KG3D_CompilePS%(([%w_]+)(%([%w_/%*,%s]*%))%)";
    local szFuncName1, szFuncName2, szParam = string.match(szLine, szPattern);
	print(szFuncName1, szFuncName2, szParam);
end
-- TestGetAssemblyFunctionName();

------------------------------------------------------------------------------------------------------
local ExtractDataSheetWithBrace = function (srcStr, sep)
	local sep = sep or ","
	local tbData = {};

	local nLen = string.len(srcStr);
	local tbMatch = {};
	local nLevel = 0;
	local tbCur = tbData;
	local tbLevels = {};
	tbLevels[1] = tbCur;
	for i = 1, nLen do
		local c = string.sub(srcStr, i, i);
		if c == '{' then
			nLevel = nLevel + 1;
			table.insert(tbMatch, i);
			if nLevel ~= 1 then
				tbCur = {};
				tbLevels[nLevel] = tbCur
				table.insert(tbLevels[nLevel - 1], tbCur);
			end
		elseif c == '}' then
			local nStart = table.remove(tbMatch, #tbMatch);
			local nEnd = i;
			local nSubString = string.sub(srcStr, nStart + 1, nEnd - 1);
			if nLevel ~= 1 and #tbCur <= 0 then
				local tbParam = string.split(nSubString, sep);
				for k, v in ipairs(tbParam or {}) do
					table.insert(tbCur, v);
				end
				nLevel = nLevel - 1;
				tbCur = tbLevels[nLevel];
			end
		end
	end

	return tbData;
end

function TestExtractDataSheetWithBrace()
	-- local tb1 = ExtractDataSheetWithBrace("{巡逻安民,训练新兵,护卫县令,维护治安}");
	-- local tb1 = ExtractDataSheetWithBrace("{{赵振华|父亲}{李秀珍|母亲}{王燕儿|妻子}{赵子龙|儿子}{赵秋莲|女儿}}", "|");
	-- local tb1 = ExtractDataSheetWithBrace("{{{a|b}}{c|d}{e|f}}", "|");
	local tb1 = ExtractDataSheetWithBrace("{}");
	-- for k, v in pairs(tb1) do
	-- 	-- print(k, v)
	-- 	for k1, v1 in pairs(v) do
	-- 		print(k1, v1)
	-- 	end
	-- end
end
-- TestExtractDataSheetWithBrace()


------------------------------------------------------------------------------------------------------