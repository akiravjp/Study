
async function test(ctx,next){
    doThing().then(console.log('done Thing'))
    doAnotherThing();
    console.log('this way');
}

  async function doThing() {
    // doA();
    // doB();
	
	await doA();
    await doB();
  }
  
  function doAnotherThing() {
    console.log('do another thing')
  }
  
  async function doA() {
    return new Promise(resove => {
      setTimeout(() => {
        console.log('done A')
        resove()
      }, 1000)
    })
  }
  
  async function doB() {
    return new Promise(resove => {
      setTimeout(() => {
        console.log('done B')
        resove()
      }, 100)
    })
  }
  
  // test()
  
async function test1(){
	var a = await 3;
	return a;
}
// console.log(test1())
// console.log(test1().then((resolve, reject)=>{
	// console.log('resolve:', resolve)
// }))

  
///////////////////////////////////////////////////////////////
// wait ms milliseconds
function wait(ms) {
  return new Promise(r => setTimeout(r, ms));
}

async function hello() {
  await wait(500);
  return 'world';
}

// console.log(111)
// a = hello().then(resolve=>{
	// console.log(333, resolve)
// })
// a = Promise.all([(async()=>console.log(await hello()))()])
// console.log(222)
// console.log(a)

///////////////////////////////////////////////////////////////
// reference: https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Statements/async_function
var resolveAfter2Seconds = function() {
  console.log("starting slow promise");
  return new Promise(resolve => {
    setTimeout(function() {
      resolve("slow");
      console.log("slow promise is done");
    }, 2000);
  });
};

var resolveAfter1Second = function() {
  console.log("starting fast promise");
  return new Promise(resolve => {
    setTimeout(function() {
      resolve("fast");
	  // Promise.reject("fast")
      console.log("fast promise is done");
    }, 1000);
  });
};

var sequentialStart = async function() {
  console.log('==SEQUENTIAL START==');

  // 1. Execution gets here almost instantly
  const slow = await resolveAfter2Seconds();
  console.log(slow); // 2. this runs 2 seconds after 1.

  const fast = await resolveAfter1Second();
  console.log(fast); // 3. this runs 3 seconds after 1.
}

var concurrentStart = async function() {
  console.log('==CONCURRENT START with await==');
  const slow = resolveAfter2Seconds(); // starts timer immediately
  const fast = resolveAfter1Second(); // starts timer immediately
  // console.log(111, slow, fast)
  // 1. Execution gets here almost instantly
  console.log(await slow); // 2. this runs 2 seconds after 1. 1����������ִ���ˣ�����û�д�ӡfast��������ƾ����첽��Ϣ���е�ԭ��ɣ�ǰ��һ��Ҫ��2�뻹û������
  // 1���2�벻�Ǻ����ԣ��ĳ�1���3������Զ��ˣ�fast promise is done��ӡ֮���һ��Ŵ�ӡ�����
  // ��Ϊ��await�����Ա�֤˳��ִ�У���������fast�Ŵ�ӡ
  console.log(await fast); // 3. this runs 2 seconds after 1., immediately after 2., since fast is already resolved
  // �ܽ᣺
  // 1.������ʱ��ͬʱ���У������ܹ�ֻ��Ҫ2��
  // 2.await��֤˳��ִ�У���˵���صĽ��˳�򣿵���ִ��˳�򲢲���֤����Ϊfast promise is done�����ȴ�ӡ�ġ�����3�������ش��������Ļ����ǣ�resolveAfter2Seconds��resolveAfter1Secondͬʱ���У������Ǳ���������Ϊawait����������fast promise is done����ִ���꣬�����ȴ�ӡ��
  // 3.await ���ʽ����ͣ��ǰ async function ��ִ�У��ȴ� Promise ������ɡ����Ե�һ��slow��һ��Promise����Ҫ2���ֵ�ִ��ʱ�䣬��ʹ�ڶ���Promise(fast)�Ѿ���1���ӵ�ʱ��ִ�����ˣ���������async������ͣ�ˣ�������Ҫ�ڶ���console.log��ִ�У�����Ϣ����û�й�ϵ��
  // �����Ƿ�ʹ�� await���첽�������᷵�� Promise. ��һ����֤��concurrentStart������һ��Promise��������ں������һ��return�Ļ�
  console.log('end');
  return slow
}

var concurrentPromise = function() {
  console.log('==CONCURRENT START with Promise.all==');
  return Promise.all([resolveAfter2Seconds(), resolveAfter1Second()]).then((messages) => {
    console.log(messages[0]); // slow
    console.log(messages[1]); // fast
  });
}

var parallel = async function() {
  console.log('==PARALLEL with await Promise.all==');
  
  // Start 2 "jobs" in parallel and wait for both of them to complete
  await Promise.all([
		// ��ͷ����������console.log�Ľ��
		// ��������await resolveAfter2Seconds����
      (async()=>console.log(await resolveAfter2Seconds()))(),
      (async()=>console.log(await resolveAfter1Second()))()
  ]);
  // �ܽ᣺
  // 1.
}

// This function does not handle errors. See warning below!
var parallelPromise = function() {
  console.log('==PARALLEL with Promise.then==');
  resolveAfter2Seconds().then((message)=>console.log(message));
  resolveAfter1Second().then((message)=>console.log(message));
}

// sequentialStart(); // after 2 seconds, logs "slow", then after 1 more second, "fast"

// wait above to finish
// setTimeout(concurrentStart, 4000); // after 2 seconds, logs "slow" and then "fast"
// console.log(concurrentStart())
// Promise.all([(async()=>console.log(await concurrentStart()))()])

// wait again
// setTimeout(concurrentPromise, 7000); // same as concurrentStart

// wait again
// setTimeout(parallel, 10000); // truly parallel: after 1 second, logs "fast", then after 1 more second, "slow"
// setTimeout(parallel, 1000); // truly parallel: after 1 second, logs "fast", then after 1 more second, "slow"

// wait again
// setTimeout(parallelPromise, 13000); // same as parallel
// setTimeout(parallelPromise, 1000); // same as parallel


//////////////////////////////////////////////////////
// await: https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Operators/await
function resolveAfter2Seconds1(x) {
  return new Promise(resolve => {
    setTimeout(() => {
      resolve(x);
	  console.log('resolveAfter2Seconds1 done.')
    }, 2000);
  });
}

// ���һ�� Promise �����ݸ�һ�� await ��������await ���ȴ� Promise ����������ɲ������䴦������
async function f1() {
  var x = await resolveAfter2Seconds1(10);
  console.log(x); // 10
}
// f1();

// �����ֵ����һ�� Promise��await ��Ѹ�ֵת��Ϊ�����������Promise��Ȼ��ȴ��䴦������
async function f2() {
  var y = await 20;
  console.log(y); // 20
}
// f2();

// ��� Promise �����쳣�����쳣ֵ���׳���
async function f3() {
  try {
    var z = await Promise.reject(30);
  } catch (e) {
    console.log(e); // 30
  }
}
// f3();

//////////////////////////////////////////
var resolveAfterNSecond = function(time) {
  console.log("starting promise, wait: " + time);
  return new Promise((resolve, reject) => {
    setTimeout(function() {
		if(time%2000 === 0){
			resolve(time);
		}
		else{
			reject('error')
		}
      
	  // Promise.reject("fast")
      console.log("promise is done, time = ", time);
    }, time);
  });
};

function forPromiseAll(n){
	var l = [];
	for(var i = 0; i < n; ++i){
		var r = resolveAfterNSecond((i+1) * 1000);
		l.push(r);
	}
	Promise.all(l)
	.then((ret)=>{
		console.log(ret);
	});
}
forPromiseAll(2);

async function forAsyncAwait(n){
	for(var i = 0; i < n; ++i){
		await resolveAfterNSecond((i+1) * 1000);
	}
	
	console.log('end');
}
// forAsyncAwait(3);