class Rey
  attr_accessor :nombre

  def initialize(nombre)
    @nombre = nombre
  end
end

class Castillo
  attr_accessor :nombre

  def initialize(nombre)
    @nombre = nombre
  end
end

class Ejercito
  attr_accessor :descripcion, :n_efectivos

  def initialize(descripcion, n_efectivos)
    @descripcion = descripcion
    @n_efectivos = n_efectivos
  end
end

class Realm
  def initialize
    @rey = nuevo_rey
    @castillo = nuevo_castillo
    @ejercito = nuevo_ejercito
  end

  def describe
    puts "I am #{@rey.nombre}, king of the #{self.class.name}"
    puts "This is #{@castillo.nombre}, home of the #{self.class.name}"
    puts "This is the powerful #{@ejercito.descripcion} army " +
         "composed of #{@ejercito.n_efectivos} #{self.class.name}"
  end
end

class Orcs < Realm
  def nuevo_rey
    Rey.new("Melkor")
  end

  def nuevo_castillo
    Castillo.new("Isengard")
  end

  def nuevo_ejercito
    Ejercito.new("Orcs", 20000)
  end
end

class Elfs < Realm # Elves?
  def nuevo_rey
    Rey.new("Thranduil")
  end

  def nuevo_castillo
    Castillo.new("Woodlands")
  end

  def nuevo_ejercito
    Ejercito.new("Elves", 2500)
  end
end

class Humans < Realm
  def nuevo_rey
    Rey.new("Aragorn")
  end

  def nuevo_castillo
    Castillo.new("Silmarillion")
  end

  def nuevo_ejercito
    Ejercito.new("Soldiers", 4500)
  end
end


orcs = Orcs.new
elfs = Elfs.new
humans = Humans.new

orcs.describe
puts "-"*60
elfs.describe
puts "-"*60
humans.describe