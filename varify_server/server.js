const grpc = require("@grpc/grpc-js");
const message_proto = require("./proto");
const emailModule = require('./email')
const globalModule = require('./global')
const { v4: uuidv4 } = require('uuid');


async function getVarifyCode(call, callback) {
    console.log('email is ', call.request.email)
    try {
        uniqueId = uuidv4()
        console.log('uniqueId is', uniqueId)
        let strText = '您的验证码为 ' + uniqueId + ' 请在三分钟内完成注册'

        let mailOptions = {
            from: 'Iris <1147323330@qq.com>',
            to: call.request.email,
            subject: '验证码',
            text: strText,
        };

        let sendRes = await emailModule.sendEmail(mailOptions)
        console.log('send response is ', sendRes)

        callback(null, {
            email: call.request.email,
            error: globalModule.Errors.Success
        })
    } catch (error) {
        console.log('catch error is ', error)

        callback(null, {
            email: call.request.email,
            error: globalModule.Errors.Success
        })
    }
}

function main() {
    let server = new grpc.Server()
    server.addService(message_proto.VarifyService.service, { GetVarifyCode: getVarifyCode });
    server.bindAsync("0.0.0.0:8081", grpc.ServerCredentials.createInsecure(), () => {
        console.log("grpc server started");
    })
}

main()