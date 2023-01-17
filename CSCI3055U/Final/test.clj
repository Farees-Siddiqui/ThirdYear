;; given the following binary tree representation:
;; 10
;; / \
;; 7 15
;; / \ 
;; 3 9

;; model the tree shown above without using the tree function
(def root {:value 10
           :left {:value 7
                  :left {:value 3
                         :left nil
                         :right nil}
                  :right {:value 9
                          :left nil
                          :right nil}}
           :right {:value 15
                   :left nil
                   :right nil}})


;; implement the binary search function so that it works for all children of the root using loop/recur
;; the function should return true if the value is found in the tree
;; and false if it is not found
(defn binary-search [tree value]
  (loop [tree tree]
    (if (nil? tree)
      false
      (if (= (:value tree) value)
        true
        (recur (if (< value (:value tree))
                  (:left tree)
                  (:right tree)))))))

;; modify the binary search function so that it uses reduce instead of loop/recur
(defn binary-search [tree value]
  (reduce (fn [acc tree]
            (if (nil? tree)
              false
              (if (= (:value tree) value)
                true
                (if (< value (:value tree))
                  (:left tree)
                  (:right tree)))))
          false
          [tree]))

;; using reduce, get all the values from root, output should be [10 7 3 9 15]
(defn get-values [tree]
  (reduce (fn [acc tree]
            (if (nil? tree)
              acc
              (conj acc (:value tree))))
          []
          [tree]))

;; implement a lambda calculus expression nth that returns the nth component of a pair
;; the definition of a pair is: /a./b./f./f a b
