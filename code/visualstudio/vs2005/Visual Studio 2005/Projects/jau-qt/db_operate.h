#ifndef _DB_OPERATE_H_
#define _DB_OPERATE_H_

#ifdef  _USE_MYSQL_
#define SQL_QUERY_CHINESE	"select * from %s where chinese='%s'"
#define SQL_QUERY_All		"select * from %s"
#define SQL_INSERT_STR		"insert into %s values('%s','%s')"
#define SQL_UPDATE_STR		"update %s set translate='%s' where chinese='%s'"
#define SQL_DELETE_TABLE	"delete from %s"
#define SQL_DELETE_STR		"delete from %s where chinese='%s'"
#define SQL_TABLE_CREATE	"create table if not exists %s (chinese text character\
				 set gbk, primary key (chinese(200)), translate text)"

typedef struct DATABASE_INFO{
	char	szUser[32];
	char	szPasswd[32];
	char	szDatabaseSvr[32];
	char	szDatabase[32];
	char	szTable[32];
	int	nPort;
	int	nLanguageType;
}DataBase;

#else
typedef struct DATABASE_INF{
	int	nLanguageType;
	char	szDBName[32];
}DataBase;
#endif //_USE_MY_SQL

#define MAX_BUF_2048		2048
#define MAX_CHINESE_LEN		MAX_BUF_2048
#define MAX_TRANS_LEN		MAX_BUF_2048*3
#define MAX_SQL_LEN1		MAX_CHINESE_LEN+256
#define MAX_SQL_LEN2		MAX_CHINESE_LEN+MAX_TRANS_LEN+256
#define MAX_LINE_LEN		MAX_BUF_2048*5

enum TRANS_STATE{		/* record type */
	TS_NOTRANSLATE = 1,  	/* not translated record*/
	TS_FILENAME,		/* file name record */
	TS_PATH,		/* path record */
	TS_ERROR,		/* error record which is not recognised*/
	TS_TRANSLATED,		/* translated record */
	TS_ALL,
	TS_STATUS_NUM,
};

/* �������������Ͷ��壬 */
enum LANGUAGE_TYPE{
	TEMP,			/* ��ʱ�ֵ� */
	TRANTIONAL,		/* ���� */
	ENGLISH,		/* Ӣ�� */
	VIETNAM,		/* Խ�� */
	CAMBODIA,		/* ����կ */
	LANGUAGE_NUM,
};
/* ���º���mysql�汾��berkeleydb�汾��jau��ʵ�ֲ�ͬ */
int  db_init(int nClearTable);
void db_uninit();

/* ����һ����������ĺͷ������Ӧ�ļ�¼�����ݿ��� */
int  update_trans_to_db(const char* pcszChinese, const char* pcszTrans);
/* ����һ��û�з�������ļ�¼�����ݿ��� */
int  insert_notrans_to_db(const char* pcszChinese);
/* ��ȡĳ����¼��Ӧ�ķ��� */
int  get_trans_from_db(char* pChinese, char* pTranslate, int nTransSize);
/* ��ѯĳ�����ļ�¼��Ӧ�ķ��룬���ndeleteΪ1,���ѯ��ֱ�ӽ��ü�¼�����ݿ���ɾ���� */
int  query_record_from_db(const char* pcszChinese, int nDelete = 0);
/* ����һ����������ĺͷ������Ӧ�ļ�¼�����ݿ��� */
int  insert_to_db(const char* pcszChinese, const char* pcszTrans);

/* �������������������汾��ʵ������ͬ�� */
/* ��һ�������ļ�������Ӧ�ķ����ļ��ж�ȡ��Ӧ���н�����µ����ݿ��У�
   nOldTransָ�Ƿ��Լ����ϵĹ��߳�ȡ�ļ�¼�ķ�ʽ�Լ�¼���и��� */
int  update_trans_to_db_from_files(const char* pcszChineseFile,
				   const char* pcszTransFile,
				   int nOldTrans);

/* ��һ���ļ���ÿ�����У��ѵ�һ����Ϊ�����ļ����ļ������ѵڶ�����Ϊ��Ӧ�ķ�����ļ�����Ȼ��
   ʹ��update_trans_to_db_from_files����������������ļ��е����ݸ��µ����ݿ��� */
int  update_trans_to_db_from_a_file(const char* pcszFileName, int nOldTrans);

/* �������ݿ��е�ÿһ���ѷ���ļ�¼����ִ��ĳ��ָ���Ĳ�����������Ҫ����ļ�¼�ֱ���������ĺͷ��������ļ���
   pcszChineseFileΪִ�в���֮����Ҫ��¼�����ļ�¼��д���ļ�
   pcszTransFileΪִ�в���֮����Ҫ��¼�ķ����¼��д���ļ�
   pcszoperationΪ��Ҫִ�еĲ������ַ���*/
int  traverse_to_do_something(const char* pcszChineseFile,
			      const char* pcszTransFile,
			      const char* pcszOperation);

#endif // _DB_OPERATE_H_
