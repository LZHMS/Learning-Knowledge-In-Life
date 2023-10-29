/*-----------------数据库上机实验总结-------------*/

/* Note 1: 创建数据库模式
	CREATE SCHEMA <模式名> AUTHORIZATION <用户名>;
*/
CREATE SCHEMA S-T AUTHORIZATION [Zhihao Li];

/* Note 2: 删除数据库模式
	DROP SCHEMA <模式名> <CASCADE|RESTRICT>;
*/
DROP SCHEMA S-T CASCADE;

/* Note 3: 定义基本表
	CREATE TABLE <表名>(
				<列名> <数据类型> [<列级完整性约束条件>]
				[,<列名> <数据类型> [<列级完整性约束条件>]]
			  ...
				[,<表级完整性约束条件>]
	);
*/
CREATE TABLE Student(
	Sno CHAR(9) PRIMARY KEY,
	Sname CHAR(9) UNIQUE,
	Ssex CHAR(2),
	Sage SMALLINT,
	Sdept CHAR(20)
	);
CREATE TABLE Course(
	Cno CHAR(4) PRIMARY KEY,
	Cname CHAR(40),
	Cpno CHAR(4),
	Ccredit SMALLINT,
	FOREIGN KEY(Cpno) REFERENCES Course(Cno)
	);
CREATE TABLE SC(
	Sno CHAR(9),
	Cno CHAR(4),
	Grade SMALLINT,
	PRIMARY KEY(Sno, Cno),
	FOREIGN KEY(Sno) REFERENCES Student(Sno),
	FOREIGN KEY(Cno) REFERENCES Course(Cno)
	);
/* Note 4: 修改基本表
	ALTER TABLE <表名>
		[ ADD [COLUMN] <新列名> <数据类型> [完整性约束]]
		[ ADD <表级完整性约束>]
		[ DROP [COLUMN] <列名> [CASCADE|RESTRICT]]
		[ DROP CONSTRAINT <完整性约束名> [CASCADE|RESTRICT]]
		[ ALTER COLUMN <列名> <数据类型> ];
*/
ALTER TABLE Student ADD S_entrance DATE;
ALTER TABLE Student ALTER COLUMN Sage INT;
ALTER TABLE Course ADD UNIQUE(Cname);

/* Note 5: 删除基本表
	DROP TABLE <表名>[RESTRICT|CASCADE];
*/
CREATE VIEW IS_Student AS 
	SELECT Sno,Sname,Sage
	FROM Student
		WHERE Sdept='IS';

DROP TABLE Student RESTRICT;

/* Note 6: 索引的建立
	CREATE [UNIQUE] [CLUSTER] INDEX <索引名> 
		ON <表名>(<列名>[<次序>][,<列名>[<次序>]]...)；	
*/	
CREATE UNIQUE INDEX Stusno ON Student(Sno);
CREATE UNIQUE INDEX Coucno ON Course(Cno);
CREATE UNIQUE INDEX SCno ON SC(Sno ASC, Cno DESC);

/* Note 7: 索引的修改
	ALTE INDEX <旧的索引名> RENAME TO <新的索引名>; 	
*/
ALTER INDEX SCno RENAME TO SCSno;

/* Note 8: 索引的删除
	DROP INDEX <索引名> ON <表名>;
	DROP INDEX <表名>.<索引名>;
*/
DROP INDEX Stusno ON Student;
/* = DROP INDEX Student.Stusno; */