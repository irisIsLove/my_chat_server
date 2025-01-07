const grpc = require("@grpc/grpc-js");
const message_proto = require("./proto");
const emailModule = require('./email')
const globalModule = require('./global')
const { v4: uuidv4 } = require('uuid');
const redisModule = require('./redis')


async function getVarifyCode(call, callback) {
    console.log('email is ', call.request.email)
    try {
        let queryRes = await redisModule.getRedis(globalModule.codePrifix + call.request.email)
        console.log('query result is ', queryRes)
        let uniqueId = queryRes
        if (queryRes == null) {
            uniqueId = uuidv4()
            if (uniqueId.length > 4) {
                uniqueId = uniqueId.substring(0, 4)
            }

            let setExpire = await redisModule.setRedisExpire(globalModule.codePrifix + call.request.email, uniqueId, 600)
            if (!setExpire) {
                callback(null, {
                    email: call.request.email,
                    error: globalModule.Errors.RedisError
                })
                return
            }
        }
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
            error: globalModule.Errors.Exception
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