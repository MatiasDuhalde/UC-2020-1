class EncriptionObject
  def encrypt(string)
    string
  end

  def decrypt(string)
    string
  end
end

class RotDecorator
  def initialize(decorator, n)
    @decorator = decorator
    @n = n
  end

  def encrypt(string)
    string = @decorator.encrypt(string)
    list = []
    string.split("").each do |char|
      if 96 < char.ord && char.ord < 97 + 26
        list << ((char.ord - 97 + @n) % 26 + 97).chr
      else
        list << char
      end
    end
    string = list.join("")
  end
  
  def decrypt(string)
    list = []
    string.split("").each do |char|
      if 96 < char.ord && char.ord < 97 + 26
        list << ((char.ord - 97 - @n) % 26 + 97).chr
      else
        list << char
      end
    end
    string = list.join("")
    string = @decorator.decrypt(string)
  end
end

class SimpleTransposeDecorator
  def initialize(decorator, n)
    @decorator = decorator
    @n = n
  end

  def encrypt(string)
    string = @decorator.encrypt(string)
    offset = -(@n) % string.length
    string = string[offset, string.length] + string[0, offset] 
  end
  
  def decrypt(string)
    offset = (@n) % string.length
    string = string[offset, string.length] + string[0, offset] 
    string = @decorator.decrypt(string)
  end
end

def get_random_cipher
  object = EncriptionObject.new
  recursive_part(object)
end

def recursive_part(object)
  n = (rand() * 10 ).ceil()
  if rand() < 0.5
    object = SimpleTransposeDecorator.new(object, n)
  else
    object = RotDecorator.new(object, n)
  end
  if rand() < 0.8
    recursive_part(object)
  else
    object
  end
end

# Test
cipher = get_random_cipher
puts encrypted_string = cipher.encrypt("hola mundo")
puts cipher.decrypt(encrypted_string)