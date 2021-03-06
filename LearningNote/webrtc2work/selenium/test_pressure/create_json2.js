const fs = require("fs");
//["90019168", "40019166", "60019167", "90019169", "60019170", "50019171", "90019173", "70019172", "30019174"]
// 我创建的 50019259 90019260  80019261
const arrMeeting = [
  "90019168",
  "40019166",
  "60019167",
  "90019169",
  "60019170",
  "50019171",
  "90019173",
  "70019172",
  "30019174",
  "50019259",
  "90019260",
  "80019261",
  "40019324",
  "20019325",
  "60019326",
  "70019327",
  "20019328",
  "20019329",
  "80019330",
  "20019331",
  "90019332",
  "50019333",
  "50019334",
  "40019660",
  "70019662",
  "40019663",
  "80019664",
  "40019665",
  "70019666",
  "80019667",
];

const defaultGateWayIp = "172.17.201.210";
const defaultPort = "20045";
const personPerMeeting = 1;
const phoneSection = "155000";

class creatJson {
  constructor(meeting = [], begin = 0, end = 0) {
    this.arrPerson = { pageSet: [] };
    this.meeting = meeting;
    this.begin = begin;
    this.end = end;
  }

  append(meeting = [], begin = 0, end = 0) {
    this.meeting = meeting;
    this.begin = begin;
    this.end = end;
  }

  build(newGateway, newPort) {
    let bTwoGateway = !(
      !!(typeof newGateway == "undefined") || !!(typeof newPort == "undefined")
    );
    for (
      let iter = this.begin, curMeetNumer = 1;
      iter < this.end;
      ++iter, ++curMeetNumer
    ) {
      let onePerson = {
        userName: "15500010105",
        password: "123456",
        meetingID: "90019168",
        getwayIP: defaultGateWayIp,
        port: defaultPort,
        isSpeak: 0,
        level: 3,
      };

      if (this.meeting.length * personPerMeeting >= curMeetNumer) {
        onePerson.userName = phoneSection + iter.toString();
        onePerson.meetingID = this.meeting[
          parseInt((curMeetNumer - 1) / personPerMeeting)
        ];
        if (bTwoGateway) {
          onePerson.isSpeak = curMeetNumer % personPerMeeting == 0 ? 0 : 1;
          if (onePerson.isSpeak == 0) {
            onePerson.getwayIP = newGateway;
            onePerson.port = newPort;
          }
        }

        this.arrPerson.pageSet.push(onePerson);
      } else {
        break;
      }
    }
  }

  saveAs(fileName) {
    let person = JSON.stringify(this.arrPerson);
    console.log(person);

    fs.writeFile(fileName, person, (err) => {
      if (err) console.log("write File failed");
    });
  }
}

function test_sample() {
  let testSample = new creatJson(arrMeeting, 10501,
    10600);
    testSample.build("172.17.201.210", defaultPort);
    testSample.saveAs("recv_json.json");
}

test_sample();


function test_twoGateWay() {
  let testTwo = new creatJson([], 10106, 10200);
  testTwo.build("two_gateway.json", "brtc.butel.com", "3000");
}

function test_apppend() {
  let testSample = new creatJson(arrMeeting, 10106, 10200);
  testSample.build();
  testSample.append(
    [
      "90019260",
      "80019261",
      "40019324",
      "20019325",
      "60019326",
      "70019327",
      "20019328",
      "20019329",
      "80019330",
      "20019331",
      //"90019332",
      //  "50019333"
      // "50019334"
    ],
    10201,
    10400
  );
  testSample.build();
  testSample.saveAs("Sample_json.json");
}



//test_sample();
//test_twoGateWay();
