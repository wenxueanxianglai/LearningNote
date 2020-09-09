console.log(typeof 123);
console.log(typeof '123');
console.log(typeof false);

function f() {}

console.log(typeof f);
console.log(typeof undefined);


console.log(typeof v);      // 检查一个没有声明的变量而不报错

let o = {};
let a = [];
console.log(typeof o);          // object
console.log(typeof a);          // object
console.log(typeof null);       //object


// undefined 和 null 自动转化为 false
if (!undefined) {
    console.log('undefined is false');
}

if (!null) {
    console.log('null is false');
}

// null 为空 的 对象   undefined 为无定义  NaN
