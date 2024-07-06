//
// Generated file, do not edit! Created by nedtool 5.7 from EthFrames.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "EthFrames_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(EthFrame)

EthFrame::EthFrame(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->setName("EthFrame");
    this->setByteLength(26);

    this->ethertype = 0;
    this->deadlineA = 0;
    this->deadlineR = 0;
    this->priority = 0;
    this->sw1 = false;
    this->sw2 = false;
    this->sw3 = false;
    this->sw4 = false;
    this->sw5 = false;
    this->sw6 = false;
    this->period = 0;
    this->payload = 0;
    this->burst = 0;
    this->pri = 0;
    this->e2eMax = 0;
    this->e2eAvg = 0;
}

EthFrame::EthFrame(const EthFrame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

EthFrame::~EthFrame()
{
}

EthFrame& EthFrame::operator=(const EthFrame& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void EthFrame::copy(const EthFrame& other)
{
    this->nome = other.nome;
    this->dst = other.dst;
    this->src = other.src;
    this->ethertype = other.ethertype;
    this->deadlineA = other.deadlineA;
    this->deadlineR = other.deadlineR;
    this->priority = other.priority;
    this->sw1 = other.sw1;
    this->sw2 = other.sw2;
    this->sw3 = other.sw3;
    this->sw4 = other.sw4;
    this->sw5 = other.sw5;
    this->sw6 = other.sw6;
    this->period = other.period;
    this->payload = other.payload;
    this->burst = other.burst;
    this->pri = other.pri;
    this->e2eMax = other.e2eMax;
    this->e2eAvg = other.e2eAvg;
}

void EthFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->nome);
    doParsimPacking(b,this->dst);
    doParsimPacking(b,this->src);
    doParsimPacking(b,this->ethertype);
    doParsimPacking(b,this->deadlineA);
    doParsimPacking(b,this->deadlineR);
    doParsimPacking(b,this->priority);
    doParsimPacking(b,this->sw1);
    doParsimPacking(b,this->sw2);
    doParsimPacking(b,this->sw3);
    doParsimPacking(b,this->sw4);
    doParsimPacking(b,this->sw5);
    doParsimPacking(b,this->sw6);
    doParsimPacking(b,this->period);
    doParsimPacking(b,this->payload);
    doParsimPacking(b,this->burst);
    doParsimPacking(b,this->pri);
    doParsimPacking(b,this->e2eMax);
    doParsimPacking(b,this->e2eAvg);
}

void EthFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->nome);
    doParsimUnpacking(b,this->dst);
    doParsimUnpacking(b,this->src);
    doParsimUnpacking(b,this->ethertype);
    doParsimUnpacking(b,this->deadlineA);
    doParsimUnpacking(b,this->deadlineR);
    doParsimUnpacking(b,this->priority);
    doParsimUnpacking(b,this->sw1);
    doParsimUnpacking(b,this->sw2);
    doParsimUnpacking(b,this->sw3);
    doParsimUnpacking(b,this->sw4);
    doParsimUnpacking(b,this->sw5);
    doParsimUnpacking(b,this->sw6);
    doParsimUnpacking(b,this->period);
    doParsimUnpacking(b,this->payload);
    doParsimUnpacking(b,this->burst);
    doParsimUnpacking(b,this->pri);
    doParsimUnpacking(b,this->e2eMax);
    doParsimUnpacking(b,this->e2eAvg);
}

const char * EthFrame::getNome() const
{
    return this->nome.c_str();
}

void EthFrame::setNome(const char * nome)
{
    this->nome = nome;
}

const char * EthFrame::getDst() const
{
    return this->dst.c_str();
}

void EthFrame::setDst(const char * dst)
{
    this->dst = dst;
}

const char * EthFrame::getSrc() const
{
    return this->src.c_str();
}

void EthFrame::setSrc(const char * src)
{
    this->src = src;
}

int EthFrame::getEthertype() const
{
    return this->ethertype;
}

void EthFrame::setEthertype(int ethertype)
{
    this->ethertype = ethertype;
}

::omnetpp::simtime_t EthFrame::getDeadlineA() const
{
    return this->deadlineA;
}

void EthFrame::setDeadlineA(::omnetpp::simtime_t deadlineA)
{
    this->deadlineA = deadlineA;
}

::omnetpp::simtime_t EthFrame::getDeadlineR() const
{
    return this->deadlineR;
}

void EthFrame::setDeadlineR(::omnetpp::simtime_t deadlineR)
{
    this->deadlineR = deadlineR;
}

int EthFrame::getPriority() const
{
    return this->priority;
}

void EthFrame::setPriority(int priority)
{
    this->priority = priority;
}

bool EthFrame::getSw1() const
{
    return this->sw1;
}

void EthFrame::setSw1(bool sw1)
{
    this->sw1 = sw1;
}

bool EthFrame::getSw2() const
{
    return this->sw2;
}

void EthFrame::setSw2(bool sw2)
{
    this->sw2 = sw2;
}

bool EthFrame::getSw3() const
{
    return this->sw3;
}

void EthFrame::setSw3(bool sw3)
{
    this->sw3 = sw3;
}

bool EthFrame::getSw4() const
{
    return this->sw4;
}

void EthFrame::setSw4(bool sw4)
{
    this->sw4 = sw4;
}

bool EthFrame::getSw5() const
{
    return this->sw5;
}

void EthFrame::setSw5(bool sw5)
{
    this->sw5 = sw5;
}

bool EthFrame::getSw6() const
{
    return this->sw6;
}

void EthFrame::setSw6(bool sw6)
{
    this->sw6 = sw6;
}

::omnetpp::simtime_t EthFrame::getPeriod() const
{
    return this->period;
}

void EthFrame::setPeriod(::omnetpp::simtime_t period)
{
    this->period = period;
}

int EthFrame::getPayload() const
{
    return this->payload;
}

void EthFrame::setPayload(int payload)
{
    this->payload = payload;
}

int EthFrame::getBurst() const
{
    return this->burst;
}

void EthFrame::setBurst(int burst)
{
    this->burst = burst;
}

int EthFrame::getPri() const
{
    return this->pri;
}

void EthFrame::setPri(int pri)
{
    this->pri = pri;
}

::omnetpp::simtime_t EthFrame::getE2eMax() const
{
    return this->e2eMax;
}

void EthFrame::setE2eMax(::omnetpp::simtime_t e2eMax)
{
    this->e2eMax = e2eMax;
}

::omnetpp::simtime_t EthFrame::getE2eAvg() const
{
    return this->e2eAvg;
}

void EthFrame::setE2eAvg(::omnetpp::simtime_t e2eAvg)
{
    this->e2eAvg = e2eAvg;
}

class EthFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EthFrameDescriptor();
    virtual ~EthFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EthFrameDescriptor)

EthFrameDescriptor::EthFrameDescriptor() : omnetpp::cClassDescriptor("EthFrame", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

EthFrameDescriptor::~EthFrameDescriptor()
{
    delete[] propertynames;
}

bool EthFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthFrame *>(obj)!=nullptr;
}

const char **EthFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EthFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EthFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 19+basedesc->getFieldCount() : 19;
}

unsigned int EthFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<19) ? fieldTypeFlags[field] : 0;
}

const char *EthFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nome",
        "dst",
        "src",
        "ethertype",
        "deadlineA",
        "deadlineR",
        "priority",
        "sw1",
        "sw2",
        "sw3",
        "sw4",
        "sw5",
        "sw6",
        "period",
        "payload",
        "burst",
        "pri",
        "e2eMax",
        "e2eAvg",
    };
    return (field>=0 && field<19) ? fieldNames[field] : nullptr;
}

int EthFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nome")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+2;
    if (fieldName[0]=='e' && strcmp(fieldName, "ethertype")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "deadlineA")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "deadlineR")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "sw1")==0) return base+7;
    if (fieldName[0]=='s' && strcmp(fieldName, "sw2")==0) return base+8;
    if (fieldName[0]=='s' && strcmp(fieldName, "sw3")==0) return base+9;
    if (fieldName[0]=='s' && strcmp(fieldName, "sw4")==0) return base+10;
    if (fieldName[0]=='s' && strcmp(fieldName, "sw5")==0) return base+11;
    if (fieldName[0]=='s' && strcmp(fieldName, "sw6")==0) return base+12;
    if (fieldName[0]=='p' && strcmp(fieldName, "period")==0) return base+13;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+14;
    if (fieldName[0]=='b' && strcmp(fieldName, "burst")==0) return base+15;
    if (fieldName[0]=='p' && strcmp(fieldName, "pri")==0) return base+16;
    if (fieldName[0]=='e' && strcmp(fieldName, "e2eMax")==0) return base+17;
    if (fieldName[0]=='e' && strcmp(fieldName, "e2eAvg")==0) return base+18;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EthFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "string",
        "int",
        "simtime_t",
        "simtime_t",
        "int",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "simtime_t",
        "int",
        "int",
        "int",
        "simtime_t",
        "simtime_t",
    };
    return (field>=0 && field<19) ? fieldTypeStrings[field] : nullptr;
}

const char **EthFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EthFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EthFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EthFrame *pp = (EthFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EthFrameDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EthFrame *pp = (EthFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EthFrame *pp = (EthFrame *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getNome());
        case 1: return oppstring2string(pp->getDst());
        case 2: return oppstring2string(pp->getSrc());
        case 3: return long2string(pp->getEthertype());
        case 4: return simtime2string(pp->getDeadlineA());
        case 5: return simtime2string(pp->getDeadlineR());
        case 6: return long2string(pp->getPriority());
        case 7: return bool2string(pp->getSw1());
        case 8: return bool2string(pp->getSw2());
        case 9: return bool2string(pp->getSw3());
        case 10: return bool2string(pp->getSw4());
        case 11: return bool2string(pp->getSw5());
        case 12: return bool2string(pp->getSw6());
        case 13: return simtime2string(pp->getPeriod());
        case 14: return long2string(pp->getPayload());
        case 15: return long2string(pp->getBurst());
        case 16: return long2string(pp->getPri());
        case 17: return simtime2string(pp->getE2eMax());
        case 18: return simtime2string(pp->getE2eAvg());
        default: return "";
    }
}

bool EthFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EthFrame *pp = (EthFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setNome((value)); return true;
        case 1: pp->setDst((value)); return true;
        case 2: pp->setSrc((value)); return true;
        case 3: pp->setEthertype(string2long(value)); return true;
        case 4: pp->setDeadlineA(string2simtime(value)); return true;
        case 5: pp->setDeadlineR(string2simtime(value)); return true;
        case 6: pp->setPriority(string2long(value)); return true;
        case 7: pp->setSw1(string2bool(value)); return true;
        case 8: pp->setSw2(string2bool(value)); return true;
        case 9: pp->setSw3(string2bool(value)); return true;
        case 10: pp->setSw4(string2bool(value)); return true;
        case 11: pp->setSw5(string2bool(value)); return true;
        case 12: pp->setSw6(string2bool(value)); return true;
        case 13: pp->setPeriod(string2simtime(value)); return true;
        case 14: pp->setPayload(string2long(value)); return true;
        case 15: pp->setBurst(string2long(value)); return true;
        case 16: pp->setPri(string2long(value)); return true;
        case 17: pp->setE2eMax(string2simtime(value)); return true;
        case 18: pp->setE2eAvg(string2simtime(value)); return true;
        default: return false;
    }
}

const char *EthFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EthFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EthFrame *pp = (EthFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


