class Salesman
  attr_accessor :commissions, :sponsor, :n_sponsors

  def initialize
    @commissions = 0
    @sponsor = nil
    @n_sponsors = 0
  end
  
  def pay_sponsor(commission)
    @commissions += commission
    if @sponsor
      @sponsor.pay_sponsor(commission)
    end
  end
end

class MotorcycleSalesman < Salesman
  def complete_sale(amount)
    fraction = 0.03
    commission = fraction * amount # Sin tope

    # Recibir comisión
    @commissions += commission * 10/(@n_sponsors + 10)
    # Pagar comisión a padrinos
    if @sponsor
      @sponsor.pay_sponsor(commission * 1/(@n_sponsors + 10))
    end
  end
end

class CarSalesman < Salesman
  def complete_sale(amount)
    fraction = amount < 20000000 ? 0.02 : 0.05
    commission = [fraction * amount, 2000000].min # No más de dos millones

    # Recibir comisión
    @commissions += commission * 10/(@n_sponsors + 10)
    # Pagar comisión a padrinos
    if @sponsor
      @sponsor.pay_sponsor(commission * 1/(@n_sponsors + 10))
    end
  end
end

class SalesmanFactory
  attr_accessor :salesmen

  def initialize
    @salesmen = []
  end

  def create_salesman
    # create instance
    if rand < 0.5
      salesman = MotorcycleSalesman.new
    else
      salesman = CarSalesman.new
    end

    # Assign sponsor randomly from pointer list (padrino)
    sponsor = @salesmen.sample
    # If list is empty sponsor = nil; doesn't change anything
    salesman.sponsor = sponsor
    # Check n_sponsors
    current_salesman = salesman
    while current_salesman.sponsor
      current_salesman = current_salesman.sponsor
      salesman.n_sponsors += 1
    end

    # Add instance to list
    @salesmen << salesman
    salesman
  end
end
