from twilio.rest import Client 
 
account_sid = 'AC2f623fdc83dc96bc09642962ada75185' 
auth_token = 'dbd750c7e9f973bb5df19db83764bda3' 
client = Client(account_sid, auth_token) 
 
message = client.messages.create(  
    messaging_service_sid = 'MGdc6b8b7694e1f4f89594befad1b4a417',
    body = 'Hi quaz :) hows the valorant install going',
    to = '+14165059283'
    )

print(message.sid)