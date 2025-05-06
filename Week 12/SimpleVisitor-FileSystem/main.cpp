

#include <iostream>
#include "MyString.h"

class Visitor {
public:

    virtual void visitFile(File *) = 0;
    virtual void visitDirectory(Directory*) = 0;
    virtual ~Visitor() = default;
};
class FileSystem {
protected:
    MyString name;
public:
    FileSystem(const MyString& name) : name(name) {

    }
    const MyString& getName() const {
        return name;
    }
    virtual void accept(Visitor* v)=0;
    virtual ~FileSystem() = default;
};

class File : public FileSystem {
    
    void accept(Visitor* v) override
    {
        v->visitFile(this);
    }
};
class Directory : public FileSystem {
public:
    Directory(const MyString& name) : FileSystem(name) {
        
    }
    FileSystem** children;
    int size = 0;
    int capacity = 8;
    // !!!not good encapsulation
    // !!!missing stuff here
    void accept(Visitor* v) override {
        v->visitDirectory(this);
    }

};
class FileSystemVisitor : public Visitor {

public:
    void visitFile(File* f) override {
        cout << f->getName();
    }

    void visitDirectory(Directory* dir) override {
        cout << dir->getName();
        for (int i = 0; i < dir->size; i++)
        {
            dir->children[i]->accept(this);
        }
    }
};
int main()
{
    FileSystem* f = new Directory("src/");
    Visitor* v = new FileSystemVisitor();
    f->accept(v);
    delete v;
    delete f;
}


