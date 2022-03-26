package main
import (
	"fmt"
	"github.com/garyburd/redigo/redis"
)
//go 连接池

var pool *redis.Pool

func init(){
	pool = &redis.Pool{
		MaxIdle: 8, //最大空闲链接数
		MaxActive: 0,//和数据库最大的链接数，0表示不限制
		IdleTimeout: 100, //最大空闲时间
		Dial: func()(redis.Conn, error){
			return redis.Dial("tcp", "localhost:6379")
		},
	}
}
func main(){
	conn := pool.Get()
	defer conn.Close()

	_, err := conn.Do("Set", "name", "Tome")
	if err != nil{
		fmt.Println("conn.Do err!")
		return
	}

	name, err:= redis.String(Conn.Do("Get", "name"))
	if err!=nil {
		fmt.Println(conn.Do err!"")
		return
	}
	fmt.Println(name)

	pool.Close()
	return
}