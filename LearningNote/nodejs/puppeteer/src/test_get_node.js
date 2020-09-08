const puppeteer = require('puppeteer');

(async () => {
    // 1. launch 创建一个浏览器对象
    const browser = await puppeteer.launch({headless: false,
        defaultViewport:{
            width: 1000,
            height: 800
        }
    });   
    // 2. 通过 browser对象 创建一个页面
    const page = await browser.newPage();
    // 3. page 跳转到 https://192.168.1.119:3000/
    await page.goto('https://192.168.1.119:3000/');
    // 4. 对页面截图
    await page.screenshot({path: 'example.png'});
    // 5. 关闭浏览器
    await browser.close();
})();