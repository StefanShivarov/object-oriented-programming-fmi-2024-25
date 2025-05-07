

#include <iostream>
#include "MyString.h"
class File;
class Directory;

class Visitor {

public:
    virtual void visitFile(const File* f) const = 0;
    virtual void visitDirectory(const Directory* dir) const = 0;
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
    virtual void accept(const Visitor* v) const = 0;
    virtual ~FileSystem() = default;
};
class File : public FileSystem {
public:
    File(const MyString& name) : FileSystem(name) {

    }
    void accept(const Visitor* v) const override
    {
        v->visitFile(this);
    }

};

class Directory : public FileSystem {

public:
    FileSystem** children;
    int size = 0;
    int capacity = 8;
    Directory(const MyString& name) :FileSystem(name) {
        children = new FileSystem * [capacity];
    }
    // !!!not good encapsulation
   // !!!missing stuff here
    void accept(const Visitor* v) const override
    {
        v->visitDirectory(this);
    }
};
class FileSystemVisitor :public Visitor {

public:
    void visitFile(const File* f) const override {
        cout << f->getName()<<endl;
    }


    // Inherited via Visitor
    void visitDirectory(const Directory* d) const override
    {
        cout << d->getName()<<endl;
        for (int i = 0; i < d->size; i++)
        {
            d->children[i]->accept(this);
        }

    }

};
int main()
{
    Directory* f = new Directory("src/");
    f->children[f->size++] = new File("myFile.txt");
    Visitor* v = new FileSystemVisitor();
    f->accept(v);
    delete v;
    delete f;
}


