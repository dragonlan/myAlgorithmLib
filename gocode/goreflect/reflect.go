package main
import (
	"fmt"
	"reflect"
)

type Monster struct{
	Name string `json:"name"`
	Age int `json:"age"`
	Score float32
	sex	  string
}

func (s *Monster) Set(name string, age int, score float32, sex string){
	s.Name = name
	s.Age = age
	s.Score = score
	s.sex = sex
}

func TestStruct(t interface{}){
	ptyp := reflect.TypeOf(t)
	pval := reflect.ValueOf(t)
	//如果是指针传递进来，需要通过Elem取对象
	val := pval.Elem()
	typ := ptyp.Elem()
	//为什么 val = val.Elem().Type()不行？---val已经是取过对象，val.Type()可以

	fmt.Println("val:", val, "typ:", val.Type())
	kd := val.Kind()

	if kd != reflect.Struct{
		fmt.Println("No Struct, exit")
		return
	}

	num := val.NumField()
	for i:=0;i<num;i++{
		//val.Field(i)为reflect.Value 类型，可以输出，但不能计算
		//如果要计算，需要使用断言 val.Field(i).Int()
		fmt.Println("Type name:",val.Field(i).Type().Name())
		fmt.Println("Kind name:",val.Field(i).Kind())
		//基本类型时，用Kind，struct情况下，需要用Name
		switch val.Field(i).Type().Name(){
		case "int":
			iv := val.Field(i).Int()
			fmt.Println("iv:",iv)
		case "string":
			s := val.Field(i).String()
			fmt.Println("string:", s)
		default:
			fmt.Println("Unknown type:", val.Field(i).Type())
		}
		//获取字段名字，标签, 只能用reflect.Type获取
		fmt.Printf("Field:%v, PkgPath:%v Type:%v Tagname:%v\n",
				 typ.Field(i).Name,
				 typ.Field(i).PkgPath,
				 typ.Field(i).Type.Name(),
				 typ.Field(i).Tag.Get("json"))
	}

	methodNum := pval.NumMethod()
	fmt.Println("struct method num is ", methodNum)

	var v []reflect.Value // = make([]reflect.Value, 1)
	v = append(v, reflect.ValueOf("Max"))//name
	v = append(v, reflect.ValueOf(8))//age
	v = append(v, reflect.ValueOf(float32(100)))//score
	v = append(v, reflect.ValueOf("male"))//Sex
	pval.Method(0).Call(v)

	return
}

func main(){
	monster := Monster{
		Name:"dragon",
		Age:38,
		Score:99.8,
		sex:"female",
	}

	TestStruct(&monster)
	fmt.Println(monster)
	return
}