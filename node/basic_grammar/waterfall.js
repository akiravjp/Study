var async = require('async');
var a = 10;
async.waterfall([
    function(cb) {
        console.log("getb")
        setTimeout(function() {
            if (a == 0) {
                cb(new Error("a����Ϊ0"));
            } else {
                var b = 1 / a;
                cb(null, b); //������ͨ���ص�������b������һ���������ǵ�һ��Ҫ����null�����ܵ��������е���һ�����������򣬻�ֱ�ӵ������յĻص�������Ȼ����������������ĺ���������ִ��
                //�������д��cb(b);
                //������ɣ�
                /**
                 *getb
                 *0.1
                 **/
            }
        }, 1000);
    },
    function(b, cb) {
        setTimeout(function() {
            console.log("getc")
            var c = b + 1;
            cb(null,c);
        }, 1000);
    }
], function(err, result) {
    if (err) {
        console.log(err);
    } else {
        console.log('c:' + result)
    }
});