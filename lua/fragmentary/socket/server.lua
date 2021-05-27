local socket = require ( "socket" )

local tcpServer = nil

--����ָ���˿ڵ�tcp server
local function createTCPServer( port )

    -- Create Socket
    local tcpServerSocket , err = socket.tcp()
    local backlog = 5

    -- Check Socket
    if tcpServerSocket == nil then
        return nil , err
    end

    -- Allow Address Reuse
    tcpServerSocket:setoption( "reuseaddr" , true )

    -- Bind Socket
    local res, err = tcpServerSocket:bind( "*" , port )
    if res == nil then
        return nil , err
    end

    -- Check Connection
    res , err = tcpServerSocket:listen( backlog )
    if res == nil then
        return nil , err
    end

    -- Return Server
    return tcpServerSocket

end

--�������Կͻ��˵����ӣ���������tcpClient
local tcpClient = nil
local function acceptClient()
    tcpServer:settimeout( 0 )
    clientIn , _ = tcpServer:accept()
    if clientIn then
        tcpClient = clientIn
    end
end

--���������ӵĿͻ��ˣ�tcpClient������
local function receiveLoop()
    if tcpClient ~= nil then
        local tcpClientMessage , _ = tcpClient:receive('*l')

        if ( tcpClientMessage ~= nil ) then
            print(tcpClientMessage)
            tcpClient:send( "back:" .. tcpClientMessage .. "\n")
        end
    end
end

local function main()
    tcpServer , _ = createTCPServer( 8080 )
    if tcpServer then
        -- Runtime:addEventListener( "enterFrame" , acceptClient )
        -- Runtime:addEventListener( "enterFrame" , receiveLoop )
        while true do
            acceptClient();
            receiveLoop();
        end
    end
end

main()