function doActionList(list, index) {
	console.log('doActionList.............', index);
	return new Promise(resolve => {
		if(index >= list.length) {
			return resolve("done");
		} else {
			list[index]()
			doActionList(list, index+1).then(res => resolve(res));
		}
	})
}

// doActionList([10, 9, 8, 7, 6], 0).then(res=>{
	// console.log(res);
// })


var func = [
	function(){
		
		console.log('function 1');
	},
	function(){
		console.log('function 2');
	},
]


// doActionList(func, 0).then(res=>{
	// console.log(res);
// })


function delay(sec) {
  return new Promise(resolve => {
    console.log(`waiting ${sec}s...`, new Date().toLocaleString());
    setTimeout(() => resolve(), sec);
  });
}

var dramas = [
	{
		"time": 2000,
		"func": function(sec){
		
			console.log('function 1', new Date().toLocaleString());
			return new Promise(resolve => {
				// console.log(`1 waiting ${sec}s...`, new Date().toLocaleString());
				setTimeout(() => resolve(1), sec);
			});
		},
	},
	
	{
		"time": 3000,
		"func": function(sec){
		
			console.log('function 2', new Date().toLocaleString());
			return new Promise(resolve => {
				// console.log(`2 waiting ${sec}s...`, new Date().toLocaleString());
				setTimeout(() => resolve(2), sec);
			});
		},
	},
]

function doDrama(listDrama, index) {
  return new Promise((resolve, reject) => {
    if(index >= listDrama.length) {
      return resolve({ done: true, data: "done"});
    } else {
      return resolve({ done: false });
    }
  })
  .then(res => {
    if(res.done) {
      return Promise.resolve(res.data); 
    } else {
	  return listDrama[index].func(listDrama[index].time).then(()=>{
		  doDrama(listDrama, index+1);
	  })
    }
  });
}

// doDrama(dramas, 0).then(res=>{
	// console.log('done.')
// })


function test(){
	let counter = 0;
	const max = 5;

	function waitting(sec) {
	  return new Promise(resolve => {
		console.log(`waitting waiting ${sec}s...`);
		setTimeout(() => resolve(), 1000);
	  });
	}

	function promise() {
		console.log(`promise waiting ${++counter}s...`, new Date().toLocaleString());
		return new Promise(resolve => {
			if(counter >= max) {
				counter = 0;
				return resolve("promise finish");
			} else {
				setTimeout(() => {
					promise().then(res => resolve(res));
				}, 1000);
			}
		})
	}

	function promiseElse() {
		counter++;
		return new Promise((resolve, reject) => {
			if(counter >= max) {
				return resolve({ isValid: true, data: "promiseElse finish"});
			} else {
				return resolve({ isValid: false });
			}
		})
		.then(res => {
			if(res.isValid) {
				counter = 0;
				return Promise.resolve(res.data); 
			} else {
				return waitting(counter).then(() => promiseElse());
				// console.log('111 = ', t)
				// return t;
			}
		});
	}


	// promise()
	// .then(res => {
		// console.log(res);

		// return promiseElse();
	// })
	// .then(res => {
		// console.log(res);
	// });
	promiseElse()
	.then(res=>{
		console.log(res);
	})
	
	// ����1����α�֤promiseElse finishֻ�����һ�βŴ�ӡ��
	/*
	 * (1)�ø��ӵ�����
	 * (2)promiseElse���ص���һ��Promise�����Բ���.thenִ�У���ӡ���һ����ӡ
	 * (3)promiseElse���ص�Promise����һ���أ��ǳ���Ŀӡ����ȣ�����new Promise������󡣶���new Promise.then���ص�Promise����
	 * (4)new Promise.then���صĶ�������һ��������ݹ��������ô����finish�����û����
	 * (5)������ݹ�û�н��������ص���waitting.then�������ص�Promise���󡣶���������������з��صģ�������Promise�������ԣ������ǵݹ����promiseElse()���ص�Promise������ˣ�return waitting(counter).then(() => promiseElse());��仰���ص�Promise���󣬾��൱��return promiseElse()���ص�Promise���󡣶�����ٴ�ִ��promiseElse()������ʵ���˵ݹ顣
	 */
	// ����2��promiseElse�����then�������thenִ��˳��
	// ����3��then�������������res���Ǵ�������ģ�
	// ����4��return����promise��promise.then��һ������
}
// test();

// promiseִ��˳��
function testThenOrder(){
	new Promise((resolve, reject) => {
		console.log("promise")
		resolve()
	})
    .then(() => {		// ִ��.then��ʱ������һ��promise�Ǹ����һ��.then��
        console.log("then1")
        // return new Promise((resolve, reject) => {
        new Promise((resolve, reject) => {
            console.log("then1promise")
            resolve()
        })
		.then(() => {// ִ�����.then��ʱ�����ɵ�promise������һ��then��
			console.log("then1then1")
		})
		.then(() => {
			console.log("then1then2")
		})
    })
    .then(() => {
		// ���
        console.log("then2")
    })
}
// testThenOrder();

// promise
// then 1
// then 1 promise
// then1 then1
// then 2
// then1 then2

/* С�᣺�ο�https://www.jianshu.com/p/aa3d8b3adde3
 * 1. ����1��promise��then/catch����ִ�к󷵻ص�Ҳ��һ��promise�����Զ��ͬ��then��ʱ����Ҫ��ǰһ��then���ص�promise��resolve
 * 2. ����2��then��������ֵ���ο���https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Promise/then
then�������ص�promiseû��resolve����ôthenִ����ϻ᷵��ͬ������ֵ��(������⣺��������thenִ�����ʱ��)�����Լ����ص����Promise��resolve������then2����then1 then1֮��Ŵ�ӡ���������ĳ�return new Promise����ô�ͻ���then1 then1֮ǰ��ӡ����Ϊ��ִ��then1��Promiseͬ�������ʱ���Ѿ�resovle�ˣ���ôthen1���ص�promise�ͱ�����promise�ˣ�Ҳ�ͱ�resolve�ˣ����ʱ��then2��then�ͷŵ����������ˡ�
 * 3. ����3��ͬ��ִ���꣬��ִ�ж�������Ļص������壬��ִ��timeTick����then�����Ĳ�����ָ�ĺ����壩����ִ��timeout�������õĻص�������
 ���еĸ��then1���е�Promise��resolveʱ��then1 then1�ᱻע��ŵ������С���then1 then1������ִ����ϵ�ʱ��

 * ��������Ĵ�ӡ���
 * 1.Promise�������⣺��һ�����󣬰�����״̬(fulfilled, pending, rejected)���ص���������(pending״̬�·��������then�ص�������)���Լ��ĺ�����
 * 2.Promise����new��ʱ���ͬ��ִ���Լ��ĺ����壬�����ȴ�ӡpromise
 * 3.resolve��resolve�ǻ�ı�Promise����״̬�ģ���pending�ĳ�fulfilled
 * 4.ͬ��ִ�е�һ��.then����������ע��.then������һ�����������Լ�������ͬ����ʱ���ִ���ˣ�ֻ�����Ļص������壨��������û��ִ�ж��ѡ�.then�����������������Promise״̬������ͬ�����顣���Promise״̬��fulfilled�Ͱѻص�������ŵ�timeTick�������棬�����pending״̬���ͰѺ��������Promise�Լ��Ķ������档���Ե�һ��thenִ�е�ʱ�����ĺ������Ѿ�������Tick�������档����.then�����з��أ��ο�https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Promise/then����Ϊ.then�����ĺ����嶼��û��ִ�У����Է���һ��pending״̬��Promise
 5.ͬ��ִ�еڶ���.then������ע��ڶ���.then�����Ǹ��ݵ�һ��.then�������ص�Promise�����״̬�������ġ���Ϊ��pending���������.then�����Ļص�����������˵�һ��.then�������ص�Promise����Ķ�����
 6.��һ��ѭ��ִ��Tick���У�Ҳ���ǵ�һ��.then�����ĺ����塣
 (1)��ͬ��ִ��һ��new��Promise�������壬��ӡ'then 1 promise'.�������Promise�����״̬��resolve�л�Ϊfulfilled
 (2)ͬ��ִ��then1then1���.then���������Ұ��������timeTick�����У����ҷ��ص�Promiseֱ��Ϊfulfilled�����Ƿ���ֵ��undefined
 (3)ͬ��ִ��then1then2���.then��������Ϊ����һ��.then�ص������廹û��ִ�У�����һ��pending״̬��Promise���������.then�����ص���������������Promise����Ķ�����
 (4)����������û�з����κζ��������Ը���https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Promise/then�����Promise��״̬�����fulfilled������һ��.then�������ص�Promise�����״̬�ı��ˡ����ʱ����ʵ��ִ����resolve�����л�״̬�������������ῴ���Promise�����Լ��Ķ��������ǲ����лص�������Ȼ�����Щ�ŵ�timeTick�������档���Եڶ���.then������ŵ��˶������档ע�����ʱ��then1then1��then2�ĺ����嶼��tick�����У����Ƕ�û��ִ�С��ټ���js�ǵ��̣߳���˳��ִ��tick��������Ļص������壬���Խ�������ִ��then1then1��then2
 7.�ֱ�ִ��then1then1��then2���ص������壬���Ի��ȴ�ӡthen1 then1��Ȼ����'then2'
 8.then1then1�ص�������ִ����ϵ�ʱ������Promise����Ҳ���л�Ϊfulfilled�����Ұ�then1then2�ص����������tick������
 9.���ִ��then1then2�����壬��ӡ'then1 then2'�������չ�
 */
 
 // �ο���https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Promise/then
 function testThenOrder1(){
	 // using a resolved promise, the 'then' block will be triggered instantly, 
	// but its handlers will be triggered asynchronously as demonstrated by the console.logs
	const resolvedProm = Promise.resolve(33);

	then1 = resolvedProm.then(value => {
		console.log("[log]----this gets called after the end of the main stack. the value received and returned is: " + value);
		
		then1promise = new Promise((resolve, reject) => {
            console.log("[log]----then 1 promise")
            resolve('then1promise')
        })
		console.log('then1promise =', then1promise)
		
		then1then1 = then1promise.then(() => {
			console.log("[log]----then1 then1")
			return 'then1then1'
		})
		console.log('then1then1 = ', then1then1)
		
		then1then2 = then1then1.then(() => {
			console.log("[log]----then1 then2")
			return 'then1then2'
		})
		
		console.log('then1then2 = ', then1then2)
		
		// return then1promise;
		return 1;
	});
	// instantly logging the value of thenProm
	console.log("then1 = ", then1);
	
	then2 = then1.then( value => {
		console.log("[log]----then2 = " + value);
		return 2;
		
	});
	// instantly logging the value of thenProm
	console.log('then2 = ', then2);

	// using setTimeout we can postpone the execution of a function to the moment the stack is empty
	setTimeout(() => {
		console.log('waiting.........................')
		console.log("then1 = ", then1);
		console.log("then2 = ", then2);
		console.log('then1promise = ', then1promise);
		console.log('then1then1 = ', then1then1);
		console.log('then1then1 = ', then1then2);
	});

	// setTimeout(() => {
		// console.log('waiting 1 second.....................')
		// console.log("then1 = ", then1);
		// console.log("then2 =", then2);
		// console.log('then1promise = ', then1promise);
		// console.log('then1then1 = ', then1then1);
		// console.log('then1then2 = ', then1then2);
	// }, 1000);

	// ����Ĵ�������η��أ�
	// Promise {[[PromiseStatus]]: "pending", [[PromiseValue]]: undefined}
	// "this gets called after the end of the main stack. the value received and returned is: 33"
	// Promise {[[PromiseStatus]]: "resolved", [[PromiseValue]]: 33}
 }
 // testThenOrder1();
 
 // then����return��Promise����Ĭ�ϵ�promise
 function testThenOrder2(){
	Promise.resolve("foo")
	// 1. ���� "foo" ���� "bar" ƴ�ӣ�����������Ϊ��һ�� resolve ���ء�
	.then(function(string) {
		// ���1��returnһ��promise
		// return new Promise(function(resolve, reject) {
			
		// ���2��ֱ��newһ��promise��û��return
		// new Promise(function(resolve, reject) {
			// setTimeout(function() {
				// string += 'bar';
				// resolve(string);
			// }, 1000);
		// });
		
		// ���3��ֱ��newһ��promise��û��return��������then
		new Promise(function(resolve, reject) {
			setTimeout(function() {
				string += 'bar';
				resolve(string);
			}, 2000);
		})
		.then(string=>{
			console.log('111 ', string);
		});
	})
	// 2. ���� "foobar", ����һ���첽�����д�����ַ���
	// �������ӡ������̨��, ���ǲ����������ַ������ص���һ����
	.then(function(string) {
		setTimeout(function() {
			string += 'baz';
			console.log(string);
		}, 1000)
		return string;
	})
	// 3. ��ӡ�����д��뽫������еİ�����Ϣ��
	// �ַ���ʵ����������һ���ص�����֮ǰ���ǿ��첽���봦��ġ�
	.then(function(string) {
		console.log("Last Then:  oops... didn't bother to instantiate and return " +
					"a promise in the prior then so the sequence may be a bit " +
					"surprising");

		// ע�� `string` ��ʱ������� 'baz'��
		// ��Ϊ���Ƿ���������ͨ��setTimeoutģ����첽�����С�
		console.log(string);
	});

	// logs, in order:
	// Last Then: oops... didn't bother to instantiate and return a promise in the prior then so the sequence may be a bit surprising
	// foobar
	// foobarbaz
 }
 // testThenOrder2();
 
 
 //////////////////////////////////////////////
 // catch
 function catch0(){
	 var p1 = new Promise(function(resolve, reject) {
	  resolve('Success');
	});

	p1.then(function(value) {
	  console.log(value); // "Success!"
	  throw 'oh, no!';
	}).catch(function(e) {
	  console.log(e); // "oh, no!"
	}).then(function(){
	  console.log('after a catch the chain is restored');
	}, function () {
	  console.log('Not fired due to the catch');
	});

	// ������Ϊ��������ͬ
	// p1.then(function(value) {
	  // console.log(value); // "Success!"
	  // return Promise.reject('oh, no!');
	// }).catch(function(e) {
	  // console.log(e); // "oh, no!"
	// }).then(function(){
	  // console.log('after a catch the chain is restored');
	// }, function () {
	  // console.log('Not fired due to the catch');
	// });
 }
 // catch0();
 
 function catch2(){
	 //����һ���µ� Promise �����Ѿ���
	var p1 = Promise.resolve("calling next");

	var p2 = p1.catch(function (reason) {
		//���������Զ�������
		console.log("catch p1!");
		console.log(reason);
	});

	p2.then(function (value) {
		console.log("next promise's onFulfilled"); /* next promise's onFulfilled */
		console.log(value); /* calling next */
	}, function (reason) {
		console.log("next promise's onRejected");
		console.log(reason);
	});
}
// catch2();


function catch5(num){
	var p1 = new Promise(function(resolve, reject) {
		if (num == 0){
			reject('failed')
		}
		else{
			resolve('Success');
		}
	});
	
	p1.then(function(value) {
	  console.log(value); // "Success!"
	  return Promise.resolve(value);
	}).catch(function(e) {
		console.log(e); // "oh, no!"
		return Promise.reject('oh, no!');
	}).then(function(){
		console.log('after a catch the chain is restored');
	}, function () {
		console.log('Not fired due to the catch');
	});
}
// catch5();


/////////////////////////////////////////////////////////////////
// promise all/reduce
function all0(){
	Promise.all(
	[
		Promise.reject({ code: 500, msg: "error" }),
		Promise.resolve({ code: 200, list: [] }),
		Promise.resolve({ code: 200, list: [] })
	].map(p => p.catch(e => e))
	)
	.then(res => {
		console.log("res=>", res);
	})
	.catch(error => {
		console.log("error=>", error);
	});
}
all0();