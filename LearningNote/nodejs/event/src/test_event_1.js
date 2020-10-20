const EventEmitter = require("events");

class MyEmitter extends EventEmitter {}

function test() {
  const myEmitter = new MyEmitter();
  myEmitter.on("event", () => {
    console.log("触发事件");
  });
  myEmitter.on("close", () => {
    console.log("触发事件 close");
      let arr = myEmitter.eventNames();
      //myEmitter.removeAllListeners("close");
    for (let i in arr) {
      myEmitter.removeAllListeners(arr[i]);
    }
  });

  myEmitter.emit("event");
  console.log(myEmitter.eventNames());
  myEmitter.emit("close");
  console.log(myEmitter.eventNames());
}

test();
 

//myEmitter.emit("event");

let i = 0;
