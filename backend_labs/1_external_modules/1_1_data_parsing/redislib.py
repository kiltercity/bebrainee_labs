import aioredis



class AIORedisConnectionManager:
    __slots__ = [
        '__connection_pool', '__connection',
        '__host', '__port',
        '__uname', '__upass',
        '__db_number',
        '__max_connections'
    ]

    def __init__(self, 
                 host: str = 'localhost',
                 port: int = 6379,
                 username: str = None,
                 password: str = None,
                 database: int = 1,
                 max_connections: int = 50) -> None:
        """..."""
        self.__connection_pool = None
        self.__host = host
        self.__port = port
        self.__uname = username
        self.__upass = password
        self.__db_number = database
        self.__max_connections = max_connections

    def __call__(self) -> None:
        # Connection guard
        #
        if not self.__connection_pool:
            self.__connection_pool = aioredis.ConnectionPool.from_url(
                url=f"redis://{ self.__host }:{ self.__port }",
                username=self.__uname,
                password=self.__upass,
                db=self.__db_number,
                max_connections=self.__max_connections)
            self.__connection = aioredis.Redis(
                    connection_pool=self.__connection_pool)
        return self.__connection