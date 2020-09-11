const puppeteer = require('puppeteer');
const path = require('path');

let vi_path = path.resolve('./testfile/video_test.y4m');
console.log('video path: ' + vi_path);

let au_path = path.resolve('./testfile/audio_test.wav');
console.log('audio path: ' + au_path);

(async () => {
    // 1. launch 创建一个浏览器对象
    const browser = await puppeteer.launch({
        args: [
             '--use-fake-device-for-media-stream',
             '--use-fake-device-for-media-stream', // 使用虚拟设备代替真实设备
             '--use-fake-ui-for-media-stream',     // 配合上面的
            
            '--use-file-for-fake-video-capture=' + vi_path,
            '--use-file-for-fake-audio-capture=' + au_path,
     
            `--no-sandbox`
        ],
        executablePath: 'C:\\Program\ Files\\Google\\Chrome\\Application\\chrome.exe',
        ignoreHTTPSErrors: true,                // 解决证书错误
        headless: false                         
        
    }); 

    console.log('browser create succ!')  
    // 2. 通过 browser对象 创建一个页面
    const page = await browser.newPage();
    
    // 3. page 跳转到 https://192.168.1.119:3000/
     
   // await page.tracing.start({path: './trace.json'});
    //await page.goto('file:///D:/git_note/LearningNote/LearningNote/nodejs/src/www/test_camera.html');
    await page.goto('https://192.168.1.119:3000/');
    //await page.goto('https://www.baidu.com/');
    console.log('page open succ!')  
  //  await page.tracing.stop();


    // setTimeout(() => {
    //     browser.close();
    // }, 5000);

 

    // 4. 对页面截图
    await page.screenshot({path: 'example.png'});

  //  console.log(met);

    // 5. 关闭浏览器
   // browser.close();
})();