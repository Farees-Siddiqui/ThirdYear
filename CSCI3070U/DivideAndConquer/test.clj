;; given the list articles = [{:title "Intro to science", :authors [100 200], :likes 3} {:title "Programming machines", :authors [200 300], :likes 5} {:title "The digital age", :authors [300], :likes 6} {:title "Quantum computing", :authors [300 100], :likes 4}]
;; and the list authors = [{:id 100, :name "Albert Einstein", :interest "Physics"} {:id 200, :name "Alan Turing", :interest "Computer Science"} {:id 300, :name "Jeff Dean", :interest "Programming"}]
;;Implement a function to compute the total number of :likes over all the articles.

(def articles [{:title "Intro to science" :authors [100 200] :likes 3} {:title "Programming machines" :authors [200 300] :likes 5} {:title "The digital age" :authors [300] :likes 6} {:title "Quantum computing" :authors [300 100] :likes 4}])
(def authors [{:id 100 :name "Albert Einstein" :interest "Physics"} {:id 200 :name "Alan Turing" :interest "Computer Science"} {:id 300 :name "Jeff Dean" :interest "Programming"}])

(defn total-likes[]
  (reduce + (map :likes articles)))

; implement a function (check-by-id author id) to check if the author has the specified id. The function should a boolean value.
(defn check-by-id [author id]
  (= (:id author) id))

;; Implement function (author-by-id id) that returns a list of all the authors with the specified id.
;; Hint: use the built-in function filter or for loop with :when clause. Use the (check-by-id ...) function in the filter predicate function.

(defn author-by-id [id]
  (filter #(check-by-id % id) authors))


;; Implement a function (id->name id) that maps a given id to the author name. It should return nil if the id does not exist.
;;Hint: use the authors-by-id function and first built-in function in your implementation.

(defn id->name [id]
  (let [author (first (author-by-id id))]
    (if author
      (:name author)
      nil)))

;;Implement a function (resolve-ids ids) that can resolve multiple ids to author names.
;;Hint: Use map and id->name in your implementation.

(defn resolve-ids[ids]
  (map id->name ids))

;;Implement a function to resolve the author ids in an article. The function (resolve-article article) will resolve the author ids in the given article to names.
;;Hint: use update built-in function with resolve-ids in your implementation.

(defn resolve-article [article]
  (update article :authors resolve-ids))

;Implement a function (articles-with-names) that returns all articles with the author ids resolved to names.

(defn articles-with-names []
    (map resolve-article articles))