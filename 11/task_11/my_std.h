#pragma once

#include <array>
#include <algorithm>
#include <ranges>

namespace my_std {

template<typename Container, typename ObjType>
bool has_one(const Container &C, const ObjType& Obj) {
  return std::ranges::find(C, Obj) != C.end();
}

template<typename Container, typename ...ObjTypes>
bool any_of(Container &&C, ObjTypes&&... Objs) {
  std::array ObjsArray{std::forward<ObjTypes>(Objs)...};
  return std::any_of(ObjsArray.begin(), ObjsArray.end(), [&C](auto &&Obj) {
    return has_one(std::forward<Container>(C), Obj);
  });
}


template<typename Container, typename ...ObjTypes>
bool all_of(Container &&C, ObjTypes&&... Objs) {
  std::array ObjsArray{std::forward<ObjTypes>(Objs)...};
  return std::all_of(ObjsArray.begin(), ObjsArray.end(), [&C](auto &&Obj) {
    return has_one(std::forward<Container>(C), Obj);
  });
}

template<typename Container, typename ...ObjTypes>
bool none_of(Container &&C, ObjTypes&&... Objs) {
  std::array ObjsArray{std::forward<ObjTypes>(Objs)...};
  return std::none_of(ObjsArray.begin(), ObjsArray.end(), [&C](auto &&Obj) {
    return has_one(std::forward<Container>(C), Obj);
  });
}


template<class InputIt, class OutputIt, class UnaryOp, class UnaryPred>
OutputIt transform_if(InputIt First, InputIt Last, OutputIt DFirst, 
                   UnaryOp UOp, UnaryPred Pred) {
  auto Result = std::ranges::subrange{First, Last} | std::views::filter(Pred) | std::views::transform(UOp);
  return std::ranges::copy(Result, DFirst).out;
}

}
