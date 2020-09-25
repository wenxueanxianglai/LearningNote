const { group } = require('console');
let client = require('prom-client');
let gateway = new client.Pushgateway('http://127.0.0.1:9091');
// const collectDefaultMetrics = client.collectDefaultMetrics;
// const Registry = client.Registry;
// const register = new Registry();
// collectDefaultMetrics({ register });
client.name = 'ccccccc';
console.log(client.name);
gateway.name = 'ggggggg';


const registry = new client.Registry();

// just use gauge
const gauge = new client.Gauge({
    name: 'test_metric_name',
    help: 'this value hahahahahaha',
    labelNames: ['test', 'myname']
});
gauge.labels(' testServer', 'zxp').set(664545); // Set to 10

gateway.pushAdd({ jobName: 'test', }, function (      // , groupings: {key : 'myname'}      // 这个就是label
    err,
    resp,
    body
) {
    console.log(resp);
  });
   

// const client = require('prometheus-client')

// //const client = require('prom-client');
// let gateway = new client.Pushgateway('http://localhost:9091');

// gateway.pushAdd({ jobName: 'test' }, function(err, resp, body) {}); //Add metric and overwrite old ones
// //gateway.push({ jobName: 'test' }, function(err, resp, body) {}); //Overwrite all metrics (use PUT)
// //gateway.delete({ jobName: 'test' }, function(err, resp, body) {}); //Delete all metrics for jobName

// //All gateway requests can have groupings on it
// gateway.pushAdd({ jobName: 'test', groupings: { key: 'value' } }, function(
//   err,
//   resp,
//   body
// ) {});

// //It's possible to extend the Pushgateway with request options from nodes core http/https library
// gateway = new client.Pushgateway('http://127.0.0.1:9091', { timeout: 5000 }); //Set the request timeout to 5000ms