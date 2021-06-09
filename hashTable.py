class SimpleHashTable:
    '''
    Simple hash table class
    
    Attributes 
    ----------
    num_buckets : int
        number of buckets used for chaining 
    table : list of lists
        hash table of buckets for chaining
    
    Methods
    -------
    get_hash_table_index(key) -> int
        returns index of key in hash table
    
    get_index_of_bucket(key) -> int
        returns index of key in bucket in hash table
    
    key_exists(key) -> bool
        returns true if key is alreadt in the table, otherwise false
    
    insert(key, value)
        inserts a key-value pair into the hash table
    
    remove(key)
        removes a key-value pair from the hash table corresponding to the key

    retrieve(key) -> int
        returns a value corresponding to a key in the hash table
    '''

    def __init__(self, buckets = 10):
        '''
        Parameters
        ----------
        buckets : int, optional
            number of buckets to be in the hash table with default of 10
        '''

        self.num_buckets = buckets
        self.table = [[]] * self.num_buckets

    def __get_hash_table_index(self, key):
        ''' returns index of key in hash table
        Parameters
        ----------
        key : str
            key corresponding to value in hash table 

        Returns 
        -------
        hash_table_index : int
            index of key in hash table
        '''

        hashed_key = hash(key)
        hash_table_index = hashed_key % self.num_buckets
        return hash_table_index 

    def __get_index_in_bucket(self, key):
        ''' returns index of key in bucket in hash table
        Parameters
        ----------
        key : str
            key corresponding to value in hash table 

        Returns 
        -------
        index_in_bucket : int
            index of key in bucket in hash table
        '''

        hash_table_index = self.get_hash_table_index(key)
        index_in_bucket = [kv_pair[0] for kv_pair in self.table[hash_table_index]].index(key)
        return index_in_bucket

    def key_exists(self, key):
        ''' returns true if key is alreadt in the table, otherwise false
        Parameters
        ----------
        key : str
            key corresponding to value in hash table 

        Returns 
        -------
        bool
            true if key is in the table, else false
        '''

        hash_table_index = self.get_hash_table_index(key)
        if self.table[hash_table_index] is None:
            return False
        keys = [kv_pair[0] for kv_pair in self.table[hash_table_index]]
        if keys is None or key not in keys:
            return False
        return True

    def insert(self, key, value):
        ''' inserts a key-value pair into the hash table
        Parameters
        ----------
        key : str
            key corresponding to value in hash table 
        value : int
            value corresponding to key
        '''

        if self.key_exists(key):
            self.remove(key)
        hash_table_index = self.get_hash_table_index(key)
        self.table[hash_table_index].append((key, value))

    def remove(self, key):
        ''' removes a key-value pair from the hash table corresponding to the key
        Parameters
        ----------
        key : str
            key corresponding to value in hash table 
        
        Raises
        ------
        Exception
            if key does not exist in table
        '''

        if not self.key_exists(key): 
            raise Exception("Key does not exist")
        hash_table_index = self.get_hash_table_index(key)
        index_in_bucket = self.get_index_in_bucket(key)
        del self.table[hash_table_index][index_in_bucket]
    
    def retrieve(self, key):
        ''' returns a value corresponding to a key in the hash table
        Parameters
        ----------
        key : str
            key corresponding to value in hash table 
        value : int
            value corresponding to key
        
        Raises
        ------
        Exception
            if key does not exist in table
        '''
        if not self.key_exists(key): 
            raise Exception("Key does not exist")
        hash_table_index = self.get_hash_table_index(key)
        index_in_bucket = self.get_index_in_bucket(key)
        return self.table[hash_table_index][index_in_bucket][1]

# Driver   
my_hash_table = SimpleHashTable()
my_hash_table.insert('key1', 1)
my_hash_table.insert('key2', 2)
my_hash_table.insert('key3', 3)

if my_hash_table.key_exists('key4'):
    print('Key exists')
else: 
    print('Key does not exist')

print("Key 2 corresponds to {}".format(my_hash_table.retrieve('key2')))

my_hash_table.remove('key2')

if my_hash_table.key_exists('key2'):
    print('Key exists')
else:
    print('Key does not exist')
    
    
