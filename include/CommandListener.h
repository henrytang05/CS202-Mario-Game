#ifndef COMMANDLISTENER_H
#define COMMANDLISTENER_H
class CommandListener {
public:
    CommandListener();
    virtual ~CommandListener();

    virtual void pressUp() {};
    virtual void pressDown() {};
    virtual void pressLeft() {};
    virtual void pressRight() {};
    virtual void pressEnter() {};
    virtual void pressNothing() {};
};

#endif // COMMANDLISTENER_H