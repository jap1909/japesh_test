#pragma once

#include <iostream>


class TimeStamp{
    std::string id;
    int start;
    int end;
}

class Person{
    std::string id;
    std::string name;
    std::string description;
    int type;
}

class Stage{
    std::string id;
    std::string description;

}

class Component{

    std::string name;
    int type;
    int state;
    std::string description;
    std::vector<Person> owners;
    Stage stage;
    std::vector<TimeStamp> timeLine
    boolean create(){
    }
}

class Layout{
    std:vector<Component> components;
}

class Project{
    std::string siteId="";
    std::vector<Layout> layouts;

    boolean create(std::string siteId){
        
    }
}