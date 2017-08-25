#include <iostream>
#include <string>
#include <cassert>

#include "leveldb/db.h"

int main()
{
    leveldb::DB         *db;
    leveldb::Options    options;

    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());

    std::string key("name");
    std::string value("zhangheng");

    //write
    status = db->Put(leveldb::WriteOptions(), key, value);
    assert(status.ok());

    //read
    status = db->Get(leveldb::ReadOptions(), key, &value);
    assert(status.ok());

    std::cout<< value <<std::endl;

    //delete
    status = db->Delete(leveldb::WriteOptions(), key);
    assert(status.ok());

    status = db->Get(leveldb::ReadOptions(), key, &value);
    if(!status.ok())
        std::cerr<<key<<"       "<<status.ToString()<<std::endl;
    else
        std::cout<<key<<" == "<<value<<std::endl;

    delete db;

    return 0;
}
