 ;; Consider the following for-form

 (for [k (range 200)
      :when (zero? (mod k 33))]
  (format "%d div 33" k))

;; rewrite it to the equivalent form using nested invocations of map. firlter or reduce
;; express it using the threading macro
    
    (->> (range 200)
        (filter #(zero? (mod % 33)))
        (map #(format "%d div 33" %)))

;; Consider a function, f, that reverses the keys and values of a hashmap.

;; for example (f {:a 1, :b 2}) => {1 :a, 2 :b}
;; (f {:name "Jack" :grade 100}) => {"Jack" :name, 100 :grade}

;; implement the function (defn f[m]) using loop and recur use different names for the loop and recur bindings
(defn f[m] (loop [m m, acc {}]
             (if (empty? m)
               acc
               (recur (rest m) (assoc acc (val (first m)) (key (first m)))))))

;; convert the following statement into a function
;; (map (fn [k] (format "%d div 33" k))
;;       (filter (fn [k] (zero? (mod k 33)))
;;               (range 200)))

(defn f [m]
  (map (fn [k] (format "%d div 33" k))
       (filter (fn [k] (zero? (mod k 33)))
               (range 200))))