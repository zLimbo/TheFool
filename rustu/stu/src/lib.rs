pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    #[test]
    fn var_deconstruct() {
        let (a, mut b) = (true, true);

        println!("a = {:?}, b = {:?}", a, b);

        b = true;

        assert_eq!(a, b);
    }

    #[test]
    fn decons_assign() {
        struct Struct {
            e:i32
        }

        let (a, b, c, d, e);
        (a, b) = (1, 2);
        [c, .., d, _] = [1, 2, 3, 4, 5];
        Struct {e, ..} = Struct{e: 5};

        assert_eq!([1, 2, 1, 4, 5], [a, b, c, d, e]);
    }

}
