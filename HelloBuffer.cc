/*
 * get point from buffer
 * writed by jifeng(lengyuhong1987@gmail.com)
 * 
 */

#include <string.h>
#include <v8.h>
#include <node.h>
#include <node_buffer.h>

using namespace node;
using namespace v8;
using namespace std;


class HelloBuffer: ObjectWrap
{
private:
  int m_count;
public:

  static Persistent<FunctionTemplate> s_ct;
  
  static void Init(Handle<Object> target)
  {
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    s_ct = Persistent<FunctionTemplate>::New(t);
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(String::NewSymbol("HelloBuffer"));

    NODE_SET_PROTOTYPE_METHOD(s_ct , "manageBuffer" , manageBuffer);
    target->Set(String::NewSymbol("HelloBuffer"),
                s_ct->GetFunction());
  }

  HelloBuffer() :
    m_count(0)
  {
  }

  ~HelloBuffer()
  {
  }

  static Handle<Value> New(const Arguments& args)
  {
    HandleScope scope;
    HelloBuffer* hw = new HelloBuffer();
    hw->Wrap(args.This());
    return args.This();
  }

  static Handle<Value> manageBuffer(const Arguments& args)
  {
    HandleScope scope;
    HelloBuffer* hw = ObjectWrap::Unwrap<HelloBuffer>(args.This());
    hw->m_count++;  
    Local<Value> arg1 = args[0];

    if (Buffer::HasInstance(arg1)) {
      size_t size = Buffer::Length(arg1->ToObject());
      char* bufferdata = Buffer::Data(arg1->ToObject());
      //to do with size and bufferdata
      
      return scope.Close(Number::New(size)); 
    }
    else{
      return scope.Close(Number::New(-1)); 
    }
  }


};

Persistent<FunctionTemplate> HelloBuffer::s_ct;

extern "C" {
  static void init (Handle<Object> target)
  {
    HelloBuffer::Init(target);
  }
  NODE_MODULE(HelloBuffer, init);
}