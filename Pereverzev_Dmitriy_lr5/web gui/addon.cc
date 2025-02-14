// addon_3.cc
#include <node.h>
#include "lrs/lr_3/lr_3_methods.cpp"
#include "lrs/lr_4/lr_4_methods.cpp"
#include "lrs/lr_5/lr_5_methods.cpp"

namespace lrs
{

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

//lr_3
int i = 0;
int *prefix_arr;
int len;

void addon_test_3(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);

    int ret = test(string(*expr));
    if (!ret)
    {
        i = 0;
        int j = 0;
        len = string(*expr).size();
        prefix_arr = new int[len];
        for (int elem : string(*expr))
            prefix_arr[j++] = elem;
    }
    Local<Number> RET = Number::New(isolate, ret);
    args.GetReturnValue().Set(RET);
}

void addon_step(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);

    prefix_arr = step(prefix_arr, &i, &len);
    string ret = " ";
    for (int j = 0; j < len; j++)
    {
        if (isnum(prefix_arr[j]) == 0)
        {
            ret += (char)prefix_arr[j];
            ret += ' ';
        }
        else
        {
            ret += to_string(prefix_arr[j] - '0') + ' ';
        }
    }
    Local<String> RET = String::NewFromUtf8(isolate, ret.c_str());
    args.GetReturnValue().Set(RET);
}

void addon_step_by_step(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);

    int ret = step_by_step(prefix_arr, &len);
    Local<Number> RET = Number::New(isolate, ret);
    args.GetReturnValue().Set(RET);
}

//lr_4

string forest = "";
string bin_str = "";
string bypass_width = "";
//cin >> forest;
//cделать ввод строки в forest
int *lvl = new int[100];
string *arr_val = new string[100];
int i_lvl = 1;
int index = 1;

TREE *tree = NULL;
void addon_test_4(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);

    forest = "";
    int ret = test_4(string(*expr));
    if (!ret)
    {
        forest = string(*expr);
    }

    Local<Number> RET = Number::New(isolate, ret);
    args.GetReturnValue().Set(RET);
}

void addon_take_bin_str_4(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);
    bin_str = "(";
    lvl = new int[100];
    arr_val = new string[100];
    i_lvl = 1;
    index = 1;

    tree = NULL;
    lvl[0] = -1;
    lvl[i_lvl] = -1;

    //creat arrays
    create_4(i_lvl, lvl, arr_val, forest);

    //add(tree);
    add_4(tree, i_lvl, lvl, arr_val, index);
    bypass_4(tree, bin_str);
    Local<String> RET = String::NewFromUtf8(isolate, bin_str.c_str());
    args.GetReturnValue().Set(RET);
}

void addon_bypass_width_4(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);
    bypass_width = "";
    width_4(tree, bypass_width);
    Local<String> RET = String::NewFromUtf8(isolate, bypass_width.c_str());
    args.GetReturnValue().Set(RET);
}

//lr_5

TREE_5 *tree_5 = NULL;
string input_string;
int count;

void addon_build_tree_5(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    Local<Number> arg1 = Local<Number>::Cast(args[1]);
    String::Utf8Value expr(arg0);
    string tree_str = "(";
    string value;
    int count = (int)(arg1->NumberValue());
    string input = string(*expr);
    istringstream in(input);
    tree_5 = NULL;

    for (; count > 0; count--)
    {
        in >> value;
        push_5(tree_5, value);
    }
    bypass_5(tree_5, tree_str);

    Local<String> RET = String::NewFromUtf8(isolate, tree_str.c_str());
    args.GetReturnValue().Set(RET);
}

void addon_find_and_del_5(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    String::Utf8Value expr(arg0);
    string tree_str = "(";
    string input = string(*expr);
    istringstream in(input);

    string value;
    in >> value;

    if (find_elem_5(tree_5, value) != NULL)
        if (tree_5 != NULL)
        {
            del_help_5(&tree_5, value);
        }
    if (tree_5 != NULL)
        bypass_5(tree_5, tree_str);
    else
        tree_str = "_empty";

    Local<String> RET = String::NewFromUtf8(isolate, tree_str.c_str());
    args.GetReturnValue().Set(RET);
}

void addon_test_5(const FunctionCallbackInfo<Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<String> arg0 = Local<String>::Cast(args[0]);
    Local<Number> arg1 = Local<Number>::Cast(args[1]);
    String::Utf8Value expr(arg0);
    input_string = "";
    //int ret = test_5(string(*expr));
    int ret = 0;
    if (!ret)
    {
        count = (int)(arg1->NumberValue());
        input_string = string(*expr);
    }

    Local<Number> RET = Number::New(isolate, ret);

    args.GetReturnValue().Set(RET);
}

void Init(Local<Object> exports)
{
    //lr_3
    NODE_SET_METHOD(exports, "tester_3", addon_test_3);
    NODE_SET_METHOD(exports, "step_up", addon_step);
    NODE_SET_METHOD(exports, "all_steps", addon_step_by_step);

    //lr_4
    NODE_SET_METHOD(exports, "tester_4", addon_test_4);
    NODE_SET_METHOD(exports, "take_bin_str_4", addon_take_bin_str_4);
    NODE_SET_METHOD(exports, "width_4", addon_bypass_width_4);

    //lr_5
    NODE_SET_METHOD(exports, "build_tree_5", addon_build_tree_5);
    NODE_SET_METHOD(exports, "find_and_del_5", addon_find_and_del_5);
    NODE_SET_METHOD(exports, "tester_5", addon_test_5);
}

NODE_MODULE(addon, Init)

} // namespace lrs
