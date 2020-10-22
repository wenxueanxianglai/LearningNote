var config = require('./config');

console.log(config["pageSet"]);

console.log(config["server"]);
let ar = config["pageSet"];


config.pageSet.forEach((item) => {
    console.log(item);
})
