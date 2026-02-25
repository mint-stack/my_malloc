require "minitest/autorun"
require "my_malloc"

class MyMallocTest < Minitest::Test
  def test_inspect
    assert_match %r(^#<MyMalloc:),
      MyMalloc.new(5).free.inspect
  end
end
