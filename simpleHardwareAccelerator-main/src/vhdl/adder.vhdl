library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Adder_Accelerator is
  Port (
    clk   : in  std_logic;  -- Clock signal
    start : in  std_logic;  -- Start signal
    A     : in  std_logic_vector(3 downto 0);  -- First input
    B     : in  std_logic_vector(3 downto 0);  -- Second input
    sum   : out std_logic_vector(3 downto 0);  -- Output sum
    done  : out std_logic  -- Done signal
  );
end Adder_Accelerator;

architecture Behavioral of Adder_Accelerator is
  signal sum_reg : std_logic_vector(3 downto 0) := (others => '0'); 
  signal done_reg : std_logic := '0';

begin
  process (clk)
  begin
    if rising_edge(clk) then
      if start = '1' then
        sum_reg <= A + B;  -- Perform addition
        done_reg <= '1';   -- Set done flag
      else
        done_reg <= '0';   -- Reset done flag when not computing
      end if;
    end if;
  end process;

  sum <= sum_reg;
  done <= done_reg;

end Behavioral;

