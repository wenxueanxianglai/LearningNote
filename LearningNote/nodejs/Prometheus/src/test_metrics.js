let client = require('prom-client');

class SingletonApple {
    constructor() {
        this.gauge =  new client.Gauge(
            {
                name: 'metric_name',
                help: 'metric_help',
                labelNames: ["id"]
            });
    }

    static getInstance() {
        if(!this.instance) {
            this.instance = new SingletonApple();
        }
        return this.instance;
    }

  }

// const gauge = new client.Gauge(
//     {
//         name: 'metric_name',
//         help: 'metric_help',
//         labelNames: ["id"]
//     });


SingletonApple.getInstance().gauge.labels("1111aaaa").set(10); // Set to 10
SingletonApple.getInstance().gauge.labels("2222aaaa").set(10); // Set to 10

let gateway = new client.Pushgateway('http://192.168.1.127:9091');
gateway.pushAdd({ jobName: 'test', groupings: { instance: 'xxxvalue' } }, function (      // , groupings: {key : 'myname'}      // 这个就是label
    err,
    resp,
    body
) {
    console.log(resp);
  });