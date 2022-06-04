# warm-nest: hostel management and complaint system
### What is warm-nest ?
It is a hostel management and complaint system, i.e. it is a software that helps the user to manage the hostel records in digital form. It containts features to manage records of hostelers, staffs and complaints. Having such records in digital form makes their management easy and also querying on them becomes a lot easier.

#### Why the name warm-nest ?
Hostel is what becomes home-like for the hostelers, it is like living in a nest where the staffs are supposed to work like the birds keeping their children feel warm and comfy. Hence, the name warm-nest.

### How to Build
1. Download and Install Qt (if not already) on your system from https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4
2. Download and Install mariadb/conncpp connector from https://mariadb.com/downloads/connectors/connectors-data-access/cpp-connector/
Open the project in QtCreator and build the project.

### Requirements to run the application:
1. MariaDB or Mysql server running on local host.
2. A prebuild database that is to be used for the storage of hostel relevant records.
3. (optional)* Three tables with the given below names (without quotes) and schemas, respectively:

"hostelers" :
| Field             | Type                | Null | Key | Default | Extra |
|-------------------|---------------------|------|-----|---------|-------|
| room              | varchar(4)          | NO   |     | NULL    |       |
| roll              | int(8) unsigned     | NO   | PRI | NULL    |       |
| name              | varchar(20)         | NO   |     | NULL    |       |
| branch            | varchar(10)         | NO   |     | NULL    |       |
| phone             | bigint(20) unsigned | NO   | UNI | NULL    |       |
| email             | varchar(20)         | NO   | UNI | NULL    |       |
| emergency_contact | bigint(20) unsigned | NO   |     | NULL    |       |
| remark            | varchar(50)         | YES  |     | NULL    |       |

"staffs" :
| Field       | Type                | Null | Key | Default | Extra |
|-------------|---------------------|------|-----|---------|-------|
| floor_block | varchar(3)          | NO   |     | NULL    |       |
| staff_id    | int(8) unsigned     | NO   |     | NULL    |       |
| name        | varchar(20)         | NO   |     | NULL    |       |
| designation | varchar(15)         | NO   |     | NULL    |       |
| phone       | bigint(20) unsigned | NO   | PRI | NULL    |       |
| email       | varchar(20)         | NO   | UNI | NULL    |       |
| remark      | varchar(50)         | YES  |     | NULL    |       |

"complaints" :
| Field        | Type                | Null | Key | Default | Extra          |
|--------------|---------------------|------|-----|---------|----------------|
| complaint_id | bigint(20) unsigned | NO   | PRI | NULL    | auto_increment |
| date         | date                | NO   |     | NULL    |                |
| roll         | int(8) unsigned     | NO   |     | NULL    |                |
| category     | varchar(15)         | NO   |     | NULL    |                |
| complaint    | varchar(50)         | NO   |     | NULL    |                |
| status       | tinyint(1)          | NO   |     | NULL    |                |
| remark       | varchar(50)         | YES  |     | NULL    |                |

*If the tables don't exist, the applicatoin will create them. Just make sure that there isn't any table in the chosen database with names same as "hostelers", "staffs" or "complaints" (without quotes) and different schema than what is supported by the application. If you want to use different schemas or names, currently you need to change the source code. A way to do that without changing the source code is yet to be implemented (see the "Future Features" section).

### Future Features:
Although the software has basic functionalities, it lacks on some  important features that are currently under development and are to be added in the future release. Some of them are:
-> make hostelers and staffs records updatable (some or all fields?)
-> sort and filter queries on fields.
-> data entry from JSON files.
-> flexibility in table schemas to fullfill different needs of end users, (currently it can be done by changing the source code only, a more user-friendly approach is yet to be added).
